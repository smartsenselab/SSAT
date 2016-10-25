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

    this->ui->columnViewAttributes->setEditTriggers(QAbstractItemView::EditKeyPressed |
                                                  QAbstractItemView::DoubleClicked);
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

    this->connect(this->ui->pushButtonRemoveCategory,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_removeCategoryPressed())
                  );

    this->connect(this->ui->pushButtonRemoveLabel,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_removeLabelPressed())
                  );
}

void DialogAnnotation::enableWidgets(const bool _enable)
{
    //this->ui->pushButtonInsertCategory->setEnabled(_enable);
    this->ui->pushButtonInsertLabel->setEnabled(_enable);
    this->ui->pushButtonRemoveCategory->setEnabled(_enable);
    this->ui->pushButtonRemoveLabel->setEnabled(_enable);
}

void DialogAnnotation::updateCoreContent()
{
    QStringList qListC = this->qCategoriesModel->stringList();
    QStringList qListL = this->qLabelsModel->stringList();

    return;
}

void DialogAnnotation::updateWidgets()
{
    if(this->qCategoriesModel->rowCount() == 0)
    {
        this->ui->pushButtonInsertCategory->setEnabled(true);
        this->ui->pushButtonInsertLabel->setEnabled(false);
        this->ui->pushButtonRemoveCategory->setEnabled(false);
        this->ui->pushButtonRemoveLabel->setEnabled(false);
    }
    else
    {
        this->ui->pushButtonRemoveCategory->setEnabled(true);
        this->ui->pushButtonInsertLabel->setEnabled(true);
    }

    if(this->qLabelsModel->rowCount() == 0)
    {
        this->ui->pushButtonRemoveLabel->setEnabled(false);
    }
    else
    {
        this->ui->pushButtonInsertLabel->setEnabled(true);
        this->ui->pushButtonRemoveLabel->setEnabled(true);
    }
}

void DialogAnnotation::slot_initializeDialog(Core &_singleton)
{
    this->singleton = &_singleton;

    for(multimap<string, string>::iterator it = _singleton.attributes.begin(); it != _singleton.attributes.end(); it++)
    {
        this->qAttributes.insert(QString::fromStdString(it->first), QString::fromStdString(it->second));
    }

    QStringList qCategories(this->qAttributes.uniqueKeys());

    this->qCategoriesModel = new QStringListModel(this);
    this->qCategoriesModel->setStringList(qCategories);
    this->ui->columnViewAttributes->setModel(this->qCategoriesModel);

    this->qLabelsModel = new QStringListModel(this);
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
//    QStringList temp = this->qCategoriesModel->stringList();

//    int row = this->qCategoriesModel->rowCount();
//    this->qCategoriesModel->insertRows(row, 1);

//    QModelIndex index = this->qCategoriesModel->index(row);
//    this->ui->listViewCategories->setCurrentIndex(index);
//    this->ui->listViewCategories->edit(index);

//    this->updateWidgets();
}

void DialogAnnotation::slot_insertLabelPressed()
{
//    int row = this->qLabelsModel->rowCount();
//    this->qLabelsModel->insertRows(row, 1);

//    QModelIndex index = this->qLabelsModel->index(row);
//    this->ui->listViewLabels->setCurrentIndex(index);
//    this->ui->listViewLabels->edit(index);

//    this->updateWidgets();
}

void DialogAnnotation::slot_removeCategoryPressed()
{
//    QString keyCategory = this->ui->listViewCategories->currentIndex().data().toString();
//    this->qAttributes.remove(keyCategory);

//    int rowL = this->qLabelsModel->rowCount();
//    int rowC = this->ui->listViewCategories->currentIndex().row();

//    this->qLabelsModel->removeRows(0, rowL);
//    this->qCategoriesModel->removeRows(rowC, 1);

//    this->updateWidgets();
}

void DialogAnnotation::slot_removeLabelPressed()
{
//    QString keyCategory = this->ui->listViewCategories->currentIndex().data().toString();
//    QString keyLabel = this->ui->listViewLabels->currentIndex().data().toString();
//    this->qAttributes.remove(keyCategory, keyLabel);

//    int rowL = this->ui->listViewLabels->currentIndex().row();
//    this->qLabelsModel->removeRows(rowL, 1);

//    this->updateWidgets();
}


/*
#include "mainwindow.h"
#include <QApplication>
#include <QColumnView>
#include <QStandardItem>
#include <QStandardItemModel>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QMainWindow win;
    QColumnView *cview = new QColumnView;
    win.setCentralWidget(cview);

    // Create the data model
    QStandardItemModel model;

    for (int groupnum = 0; groupnum < 3 ; ++groupnum)
    {
        // Create the phone groups as QStandardItems
        QStandardItem *group = new QStandardItem(QString("Group %1").arg(groupnum));

        // Append to each group 5 person as children
        for (int personnum = 0; personnum < 5 ; ++personnum)
        {
            QStandardItem *child = new QStandardItem(QString("Person %1 (group %2)").arg(personnum).arg(groupnum));
            // the appendRow function appends the child as new row
            group->appendRow(child);
        }
        // append group as new row to the model. model takes the ownership of the item
        model.appendRow(group);
    }

    cview->setModel(&model);

    win.show();
    return app.exec();
}
*/
