#include "dialogannotation.h"
#include "ui_dialogannotation.h"
#include <qdebug.h>

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);

    this->enterPressed = new QAction(tr("id1"),this);
    this->enterPressed->setShortcuts(QList<QKeySequence>() << Qt::EnterKeyDefault);
    this->addAction(enterPressed);

    this->connectSignalSlots();
    this->enableWidgets(true);
    this->setFixedSize(this->width(), this->height());

    this->ui->treeViewAttributes->setHeaderHidden(true);
}

DialogAnnotation::~DialogAnnotation()
{
    delete ui;
}

void DialogAnnotation::connectSignalSlots()
{
    this->connect(this->enterPressed,
                  SIGNAL(triggered()),
                  this,
                  SLOT(slot_enterShortcut())
                  );
    this->connect(this->ui->pushButtonInsertCategory,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_insertCategoryPressed())
                  );

    this->connect(this->ui->pushButtonInsertLabel,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_insertLabelPressed())
                  );

    this->connect(this->ui->pushButtonRemove,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_removePressed())
                  );

    this->connect(this->ui->buttonBox,
                  SIGNAL(accepted()),
                  this,
                  SLOT(slot_accept())
                  );

    this->connect(this->ui->buttonBox,
                  SIGNAL(rejected()),
                  this,
                  SLOT(slot_reject())
                  );
}

void DialogAnnotation::enableWidgets(const bool _enable)
{
    this->ui->pushButtonInsertCategory->setEnabled(_enable);
    this->ui->pushButtonInsertLabel->setEnabled(_enable);
    this->ui->pushButtonRemove->setEnabled(_enable);
}

void DialogAnnotation::stlToModel(Attribute* _nodeAtt, QStandardItem* _qParentItem)
{
    if(_nodeAtt != NULL)
    {
        QStandardItem* qNodeTag = new QStandardItem(QString::fromStdString((*_nodeAtt).getNodeName()));
        vector<Attribute*> nodeChildren = ((*_nodeAtt).getChildren());

        vector<Attribute*>::iterator childIt;
        for(childIt = nodeChildren.begin(); childIt != nodeChildren.end(); childIt++)
        {
            this->stlToModel(*childIt, qNodeTag);
        }
        _qParentItem->appendRow(qNodeTag);
    }
}

void DialogAnnotation::modelToStl(Attribute* _parentTag, QAbstractItemModel* _qItemModel, QModelIndex _qParentIndex)
{
    for(unsigned int outer = 0; outer < _qItemModel->rowCount(_qParentIndex); ++outer)
    {
        QModelIndex qIndex = _qItemModel->index(outer, 0, _qParentIndex);
        QVariant qName = _qItemModel->data(qIndex);
        Attribute* nodeTag = new Attribute(qName.toString().toStdString());

        if(_qItemModel->hasChildren(qIndex))
        {
            this->modelToStl(nodeTag, _qItemModel, qIndex);
        }

        _parentTag->addChild(nodeTag);
    }
}


void DialogAnnotation::slot_initializeDialog(Core &_singleton)
{
    this->singleton = &_singleton;
    this->qStandardModel = new QStandardItemModel(this);

    vector<Attribute*> rootChildren = this->singleton->tagTree->getChildren();
    QStandardItem* qRootTag = new QStandardItem(QString::fromStdString(this->singleton->tagTree->getNodeName()));

    vector<Attribute*>::iterator childIt;
    for(childIt = rootChildren.begin(); childIt != rootChildren.end(); childIt++)
    {
        this->stlToModel(*childIt, qRootTag);
    }

    this->qStandardModel->appendRow(qRootTag);
    this->ui->treeViewAttributes->setModel(this->qStandardModel);
    this->ui->treeViewAttributes->setEditTriggers(QAbstractItemView::EditKeyPressed |
                                                  QAbstractItemView::DoubleClicked);

    QModelIndex first = this->qStandardModel->index(0, 0, QModelIndex());
    this->ui->treeViewAttributes->setCurrentIndex(first);

    int rowCount = this->qStandardModel->rowCount();

    // disable insert button and remove if there are no categories
    if(rowCount == 0)
    {
        this->ui->pushButtonInsertLabel->setDisabled(true);
        this->ui->pushButtonRemove->setDisabled(true);
    }
}

void DialogAnnotation::slot_insertCategoryPressed()
{
    int row = this->qStandardModel->rowCount();

    QStandardItem *category = new QStandardItem("New category");
    this->qStandardModel->appendRow(category);

    QModelIndex index = this->qStandardModel->index(row, 0);
    this->ui->treeViewAttributes->setCurrentIndex(index);
    this->ui->treeViewAttributes->edit(index);

    this->ui->pushButtonInsertLabel->setEnabled(true);
    this->ui->pushButtonRemove->setEnabled(true);

    this->connect(qStandardModel,
                  SIGNAL(itemChanged(QStandardItem*)),
                  this,
                  SLOT(slot_ConsistencyCheckCategory())
                  );

    this->disconnect(qStandardModel,
                     SIGNAL(itemChanged(QStandardItem*)),
                     this,
                     SLOT(slot_ConsistencyCheckLabel(QStandardItem*))
                     );
}

void DialogAnnotation::slot_insertLabelPressed()
{
    QStandardItem *node = this->qStandardModel->itemFromIndex(ui->treeViewAttributes->currentIndex());
    QStandardItem *parent = node->parent();

    QStandardItem *label = new QStandardItem("New label");
    if(parent)
    {
        parent->appendRow(label);
        this->ui->treeViewAttributes->expand(parent->index());
    }
    else if(!parent)
    {
        node->appendRow(label);
    }

    this->ui->treeViewAttributes->setCurrentIndex(label->index());
    this->ui->treeViewAttributes->edit(label->index());

    this->connect(qStandardModel,
                  SIGNAL(itemChanged(QStandardItem*)),
                  this,
                  SLOT(slot_ConsistencyCheckLabel(QStandardItem*))
                  );

    this->disconnect(qStandardModel,
                     SIGNAL(itemChanged(QStandardItem*)),
                     this,
                     SLOT(slot_ConsistencyCheckCategory())
                     );
}

void DialogAnnotation::slot_removePressed()
{
    int row = this->ui->treeViewAttributes->currentIndex().row();
    QModelIndex parent = this->ui->treeViewAttributes->currentIndex().parent();

    this->qStandardModel->removeRows(row, 1, parent);

    if(this->qStandardModel->rowCount() == 0)
    {
        this->ui->pushButtonInsertLabel->setDisabled(true);
        this->ui->pushButtonRemove->setDisabled(true);
    }
}

void DialogAnnotation::slot_accept()
{
    multimap<string, string> newAttributes;

    for(int outer = 0; outer < this->qStandardModel->rowCount(); outer++)
    {
        QModelIndex categoryIndex = this->qStandardModel->index(outer, 0);
        QVariant categoryName = this->qStandardModel->data(categoryIndex);

        for(int inner = 0; inner < this->qStandardModel->rowCount(categoryIndex); inner++)
        {
            QModelIndex labelIndex = this->qStandardModel->index(inner, 0, categoryIndex);
            QVariant labelName = this->qStandardModel->data(labelIndex);
            newAttributes.insert(pair<string, string>(categoryName.toString().toStdString(), labelName.toString().toStdString()));
        }
    }

    this->singleton->attributes = newAttributes;

    Attribute* newTagTree = new Attribute("ROOT", true);
    QModelIndex qIndex = this->qStandardModel->index(0, 0, QModelIndex());
    this->modelToStl(newTagTree, this->qStandardModel, qIndex);
    this->singleton->tagTree->clear();
    this->singleton->tagTree = newTagTree;
    this->accept();
}

void DialogAnnotation::slot_reject()
{
    this->reject();
}

void DialogAnnotation::slot_enterShortcut()
{
    this->accept();
}

void DialogAnnotation::slot_ConsistencyCheckCategory()
{
    int flag = 0;
    for(int outer = 0; outer < this->qStandardModel->rowCount(); outer++)
    {
        QModelIndex categoryIndex = this->qStandardModel->index(outer, 0);
        QVariant categoryName = this->qStandardModel->data(categoryIndex);

        for(int outer2 = 0; outer2 < this->qStandardModel->rowCount(); outer2++)
        {
            QModelIndex categoryIndex2 = this->qStandardModel->index(outer2, 0);
            QVariant categoryName2 = this->qStandardModel->data(categoryIndex2);
            QString str1 = categoryName.toString();
            QString str2 = categoryName2.toString();
            QByteArray ba1 = str1.toLatin1();
            QByteArray ba2 = str2.toLatin1();
            const char *c_str1 = ba1.data();
            const char *c_str2 = ba2.data();
            if(strcmp(c_str1, c_str2) == 0 && outer != outer2 )
            {
                flag = 1;
            }
        }
    }
    if(flag == 0)
    {
        this->ui->buttonBox->setEnabled(true);
        this->ui->pushButtonInsertCategory->setEnabled(true);
        this->ui->pushButtonInsertLabel->setEnabled(true);
        this->ui->pushButtonRemove->setEnabled(true);
    }
    else
    {
        this->ui->buttonBox->setEnabled(false);
        this->ui->pushButtonInsertCategory->setEnabled(false);
        this->ui->pushButtonInsertLabel->setEnabled(false);
        this->ui->pushButtonRemove->setEnabled(false);
    }
}

void DialogAnnotation::slot_ConsistencyCheckLabel(QStandardItem *node)
{
    int flag = 0;
    int row = node->parent()->row();
    QModelIndex categoryIndex = this->qStandardModel->index(row, 0);

    for(int outer = 0; outer < this->qStandardModel->rowCount(categoryIndex); outer++)
    {
        QModelIndex labelIndex = this->qStandardModel->index(outer, 0, categoryIndex);
        QVariant labelName = this->qStandardModel->data(labelIndex);

        for(int outer2 = 0; outer2 < this->qStandardModel->rowCount(categoryIndex); outer2++)
        {
            QModelIndex labelIndex2 = this->qStandardModel->index(outer2, 0, categoryIndex);
            QVariant labelName2 = this->qStandardModel->data(labelIndex2);
            QString str1 = labelName.toString();
            QString str2 = labelName2.toString();
            QByteArray ba1 = str1.toLatin1();
            QByteArray ba2 = str2.toLatin1();
            const char *c_str1 = ba1.data();
            const char *c_str2 = ba2.data();
            if(strcmp(c_str1, c_str2) == 0 && outer != outer2 )
            {
                flag = 1;
            }
        }
    }
    if(flag == 0)
    {
        this->ui->buttonBox->setEnabled(true);
        this->ui->pushButtonInsertCategory->setEnabled(true);
        this->ui->pushButtonInsertLabel->setEnabled(true);
        this->ui->pushButtonRemove->setEnabled(true);
    }
    else
    {
        this->ui->buttonBox->setEnabled(false);
        this->ui->pushButtonInsertCategory->setEnabled(false);
        this->ui->pushButtonInsertLabel->setEnabled(false);
        this->ui->pushButtonRemove->setEnabled(false);
    }
}
