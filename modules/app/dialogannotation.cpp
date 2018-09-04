#include "dialogannotation.h"
#include "ui_dialogannotation.h"
#include <qdebug.h>

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);

    this->enterPressed = new QAction(tr("id1"), this);
    this->enterPressed->setShortcuts(QList<QKeySequence>() << Qt::EnterKeyDefault);
    this->addAction(enterPressed);

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

    this->connect(this->ui->pushButtonAdd,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_addNodePressed())
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

    this->connect(this->qStandardModel,
                  SIGNAL(itemChanged(QStandardItem*)),
                  this,
                  SLOT(slot_ConsistencyCheck(QStandardItem*))
                  );
}

void DialogAnnotation::enableWidgets(const bool _enable)
{
    this->ui->pushButtonAdd->setEnabled(_enable);
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

    QModelIndex first = this->qStandardModel->index(0, 0, QModelIndex());

    this->ui->treeViewAttributes->setModel(this->qStandardModel);
    this->ui->treeViewAttributes->setCurrentIndex(first);
    this->ui->treeViewAttributes->expandAll();
    this->ui->treeViewAttributes->setEditTriggers(QAbstractItemView::EditKeyPressed |
                                                  QAbstractItemView::DoubleClicked);

    // disable insert button and remove if there are no categories
    if(this->qStandardModel->rowCount() == 0)
    {
        this->ui->pushButtonAdd->setDisabled(false);
        this->ui->pushButtonRemove->setDisabled(true);
    }

    this->connectSignalSlots();
}

void DialogAnnotation::slot_addNodePressed()
{
    QStandardItem* node = this->qStandardModel->itemFromIndex(this->ui->treeViewAttributes->currentIndex());
    QStandardItem* label = new QStandardItem("New label");
    node->appendRow(label);

    this->ui->treeViewAttributes->setCurrentIndex(label->index());
    this->ui->treeViewAttributes->edit(label->index());
}

void DialogAnnotation::slot_removePressed()
{
    QModelIndex currentIndex = this->ui->treeViewAttributes->currentIndex();
    QVariant qNodeName = this->qStandardModel->data(currentIndex);
    string nodeName = qNodeName.toString().toStdString();

    if(nodeName.compare("ROOT") != 0)
    {
        int row = this->ui->treeViewAttributes->currentIndex().row();
        int col = this->ui->treeViewAttributes->currentIndex().column();
        QModelIndex parent = this->ui->treeViewAttributes->currentIndex().parent();
        QStandardItem* node = this->qStandardModel->itemFromIndex(this->ui->treeViewAttributes->currentIndex());

        node->setText("To Remove");
        this->qStandardModel->removeRows(row, 1, parent);

        if(this->qStandardModel->rowCount() == 0)
        {
            this->ui->pushButtonAdd->setDisabled(true);
            this->ui->pushButtonRemove->setDisabled(true);
        }
    }
    else
    {
        QMessageBox message;
        message.setIcon(QMessageBox::Warning);
        message.setText("Attribute Warning");
        message.setInformativeText("You cannot remove the ROOT node");
        message.exec();
    }
}

void DialogAnnotation::slot_accept()
{
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
    this->slot_accept();
}

void DialogAnnotation::slot_ConsistencyCheck(QStandardItem *node)
{
    // ERROR: Consistency Check does not work for all same-hierarchy nodes
    bool identicalFlag = false;
    int parentRow = node->parent()->row();
    int parentCol = node->parent()->column();
    QModelIndex qParentIndex = this->qStandardModel->index(parentRow, parentCol);

    for(unsigned int outer = 0; outer < this->qStandardModel->rowCount(qParentIndex); ++outer)
    {
        QModelIndex qIndex1 = this->qStandardModel->index(outer, 0, qParentIndex);
        QVariant qName1 = this->qStandardModel->data(qIndex1);

        for(unsigned int inner = 0; inner != outer, inner < this->qStandardModel->rowCount(qParentIndex); ++inner)
        {
            if(outer != inner)
            {
                QModelIndex qIndex2 = this->qStandardModel->index(inner, 0, qParentIndex);
                QVariant qName2 = this->qStandardModel->data(qIndex2);

                string name1 = qName1.toString().toStdString();
                string name2 = qName2.toString().toStdString();
                if(name1.compare(name2) == 0)
                {
                    identicalFlag = true;
                }
            }
        }
    }

    if(identicalFlag)
    {
        this->ui->buttonBox->setEnabled(false);
        this->ui->pushButtonAdd->setEnabled(false);
    }
    else
    {
        this->ui->buttonBox->setEnabled(true);
        this->ui->pushButtonAdd->setEnabled(true);
    }
}
