#include "dialogannotation.h"
#include "ui_dialogannotation.h"

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);
    this->enterok = new QAction(tr("id1"),this);
    this->enterok->setShortcuts(QList<QKeySequence>() << Qt::EnterKeyDefault);
    this->addAction(enterok);
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
    this->connect(this->enterok,
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

void DialogAnnotation::updateCoreContent()
{
    return;
}

void DialogAnnotation::slot_initializeDialog(Core &_singleton)
{
    this->singleton = &_singleton;
    this->qStandardModel = new QStandardItemModel(this);

    for(multimap<string, string>::iterator itOuter = _singleton.attributes.begin();
        itOuter != _singleton.attributes.end();
        itOuter = _singleton.attributes.upper_bound(itOuter->first))
    {
        QStandardItem *qCategoryItem = new QStandardItem(QString::fromStdString(itOuter->first));

        for(multimap<string, string>::iterator itInner = _singleton.attributes.lower_bound(itOuter->first);
            itInner != _singleton.attributes.upper_bound(itOuter->first);
            itInner++)
        {
            QStandardItem *qLabelItem = new QStandardItem(QString::fromStdString(itInner->second));
            qCategoryItem->appendRow(qLabelItem);
        }
        this->qStandardModel->appendRow(qCategoryItem);
    }

    this->ui->treeViewAttributes->setModel(this->qStandardModel);
    this->ui->treeViewAttributes->setEditTriggers(QAbstractItemView::EditKeyPressed |
                                                  QAbstractItemView::DoubleClicked);

    QModelIndex first = this->qStandardModel->index(0, 0, QModelIndex());
    this->ui->treeViewAttributes->setCurrentIndex(first);
}

void DialogAnnotation::slot_insertCategoryPressed()
{
    int row = this->qStandardModel->rowCount();

    QStandardItem *category = new QStandardItem("New category");
    this->qStandardModel->appendRow(category);

    QModelIndex index = this->qStandardModel->index(row, 0);
    this->ui->treeViewAttributes->setCurrentIndex(index);
    this->ui->treeViewAttributes->edit(index);
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
}

void DialogAnnotation::slot_removePressed()
{
    int row = this->ui->treeViewAttributes->currentIndex().row();
    QModelIndex parent = this->ui->treeViewAttributes->currentIndex().parent();

    this->qStandardModel->removeRows(row, 1, parent);
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
    this->accept();
}

void DialogAnnotation::slot_reject()
{
    this->reject();
}
void DialogAnnotation::slot_enterShortcut(){
    this->accept();
}
