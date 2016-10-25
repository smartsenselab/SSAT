#include "dialogannotation.h"
#include "ui_dialogannotation.h"

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);

    this->connectSignalSlots();
    this->enableWidgets(false);
    this->setFixedSize(this->width(), this->height());
}

DialogAnnotation::~DialogAnnotation()
{
    delete ui;
}

void DialogAnnotation::connectSignalSlots()
{
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
}

void DialogAnnotation::enableWidgets(const bool _enable)
{
    //this->ui->pushButtonInsertCategory->setEnabled(_enable);
    //this->ui->pushButtonInsertLabel->setEnabled(_enable);
    //this->ui->pushButtonRemoveCategory->setEnabled(_enable);
    //this->ui->pushButtonRemoveLabel->setEnabled(_enable);
}

void DialogAnnotation::updateCoreContent()
{
    return;
}

void DialogAnnotation::updateWidgets()
{
    //    if(this->qCategoriesModel->rowCount() == 0)
    //    {
    //        this->ui->pushButtonInsertCategory->setEnabled(true);
    //        this->ui->pushButtonInsertLabel->setEnabled(false);
    //        this->ui->pushButtonRemoveCategory->setEnabled(false);
    //        this->ui->pushButtonRemoveLabel->setEnabled(false);
    //    }
    //    else
    //    {
    //        this->ui->pushButtonRemoveCategory->setEnabled(true);
    //        this->ui->pushButtonInsertLabel->setEnabled(true);
    //    }

    //    if(this->qLabelsModel->rowCount() == 0)
    //    {
    //        this->ui->pushButtonRemoveLabel->setEnabled(false);
    //    }
    //    else
    //    {
    //        this->ui->pushButtonInsertLabel->setEnabled(true);
    //        this->ui->pushButtonRemoveLabel->setEnabled(true);
    //    }
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

}

void DialogAnnotation::slot_listViewCategoriesClicked(QModelIndex _index)
{
    //    QMultiMap<QString, QString>::iterator it, itLower, itUpper;
    //    QString clickedItem = _index.data().toString();
    //    QStringList qLabels;

    //    this->selectedCategory = _index.data().toString();

    //    itLower = this->qAttributes.lowerBound(clickedItem);
    //    itUpper = this->qAttributes.upperBound(clickedItem);

    //    for(it = itLower; it != itUpper; it++)
    //    {
    //        qLabels.push_back(it.value());
    //    }

    //    this->qLabelsModel->setStringList(qLabels);
    //    this->ui->columnViewAttributes->setModel(this->qLabelsModel);

    //    std::cout << this->selectedCategory.toStdString() << std::endl;

    //    this->updateWidgets();
}

void DialogAnnotation::slot_listViewLabelsClicked(QModelIndex _index)
{
    this->selectedLabel = _index.data().toString();

    std::cout << this->selectedLabel.toStdString() << std::endl;

    this->updateWidgets();
}

void DialogAnnotation::slot_listViewCategoryEntered(QModelIndex _index)
{
    std::cout << "void DialogAnnotation::slot_listViewCategoryEntered()" << std::endl;
}

void DialogAnnotation::slot_listViewLabelEntered(QModelIndex _index)
{
    std::cout << "void DialogAnnotation::slot_listViewLabelEntered()" << std::endl;
}

void DialogAnnotation::slot_insertCategoryPressed()
{
    QStandardItem *category = new QStandardItem("New category");
    this->qStandardModel->appendRow(category);

    int row = this->qStandardModel->rowCount();
    QModelIndex index = this->qStandardModel->index(row, 0);

    this->ui->treeViewAttributes->setCurrentIndex(index);
    this->ui->treeViewAttributes->edit(index);

    this->updateWidgets();
}

void DialogAnnotation::slot_insertLabelPressed()
{
    int currentRow = this->ui->treeViewAttributes->currentIndex().row();
    QStandardItem *parent = this->qStandardModel->item(currentRow);

    if(parent)
    {
        this->ui->treeViewAttributes->expand(parent->index());

        QStandardItem *label = new QStandardItem("New label");
        parent->appendRow(label);

        int row = parent->rowCount();
        QModelIndex index = this->qStandardModel->index(currentRow + row, 1);

        std::cout << currentRow + row << " : " << parent->rowCount() << std::endl;

        this->ui->treeViewAttributes->setCurrentIndex(index);
        this->ui->treeViewAttributes->edit(index);
    }

    this->updateWidgets();
}

void DialogAnnotation::slot_removePressed()
{
    int row = this->ui->treeViewAttributes->currentIndex().row();
    QModelIndex parent = this->ui->treeViewAttributes->currentIndex().parent();

    this->qStandardModel->removeRows(row, 1, parent);
}
