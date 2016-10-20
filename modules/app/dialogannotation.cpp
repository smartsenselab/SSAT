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

    this->ui->listViewCategories->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                                  QAbstractItemView::DoubleClicked);
    this->ui->listViewLabels->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                              QAbstractItemView::DoubleClicked);
}

DialogAnnotation::~DialogAnnotation()
{
    delete ui;
}

void DialogAnnotation::connectSignalSlots()
{
    this->connect(this->ui->listViewCategories,
                  SIGNAL(clicked(QModelIndex)),
                  this,
                  SLOT(slot_listViewCategoriesClicked(QModelIndex))
                  );

    this->connect(this->ui->listViewLabels,
                  SIGNAL(clicked(QModelIndex)),
                  this,
                  SLOT(slot_listViewLabelsClicked(QModelIndex))
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

void DialogAnnotation::updateWidgets()
{
    if(this->categoriesModel->rowCount() == 0)
    {
        this->ui->pushButtonInsertCategory->setEnabled(true);
        this->ui->pushButtonInsertLabel->setEnabled(false);
        this->ui->pushButtonRemoveCategory->setEnabled(false);
        this->ui->pushButtonRemoveLabel->setEnabled(false);
    }

    if(this->labelsModel->rowCount() == 0)
    {
        this->ui->pushButtonRemoveLabel->setEnabled(false);
    }

    if(this->categoriesModel->rowCount() > 0)
    {
        this->ui->pushButtonRemoveCategory->setEnabled(true);
        this->ui->pushButtonInsertLabel->setEnabled(true);
    }

    if(this->labelsModel->rowCount() > 0)
    {
        this->ui->pushButtonInsertLabel->setEnabled(true);
        this->ui->pushButtonRemoveLabel->setEnabled(true);
    }

    std::cout << this->categoriesModel->rowCount() << " : " << this->labelsModel->rowCount() << std::endl;
}

void DialogAnnotation::slot_initializeDialog(Core &_singleton)
{
    multimap<string, string>::iterator it;
    QMultiMap<QString, QString> qAttributes;

    this->singleton = &_singleton;

    for(it = _singleton.attributes.begin(); it != _singleton.attributes.end(); it++)
    {
        qAttributes.insert(QString::fromStdString(it->first), QString::fromStdString(it->second));
    }

    QStringList qCategories(qAttributes.uniqueKeys());

    this->categoriesModel = new QStringListModel(this);
    this->labelsModel = new QStringListModel(this);

    this->categoriesModel->setStringList(qCategories);
    this->ui->listViewCategories->setModel(this->categoriesModel);
}

void DialogAnnotation::slot_listViewCategoriesClicked(QModelIndex _index)
{
    multimap<string, string>::iterator it, itLower, itUpper;
    string clickedItem = _index.data().toString().toStdString();
    QStringList qLabels;

    itLower = this->singleton->attributes.lower_bound(clickedItem);
    itUpper = this->singleton->attributes.upper_bound(clickedItem);

    for(it = itLower; it != itUpper; it++)
    {
        qLabels.push_back(QString::fromStdString(it->second));
    }

    this->labelsModel->setStringList(qLabels);
    this->ui->listViewLabels->setModel(this->labelsModel);
    this->ui->pushButtonInsertCategory->setEnabled(true);
    this->ui->pushButtonRemoveCategory->setEnabled(true);

    this->updateWidgets();
}

void DialogAnnotation::slot_listViewLabelsClicked(QModelIndex _index)
{
    std::cout << "void DialogAnnotation::slot_listViewLabelsClicked()" << std::endl;
    this->ui->pushButtonInsertLabel->setEnabled(true);
    this->ui->pushButtonRemoveLabel->setEnabled(true);

    this->updateWidgets();
}

void DialogAnnotation::slot_insertCategoryPressed()
{
    int row = this->categoriesModel->rowCount();
    this->categoriesModel->insertRows(row, 1);

    QModelIndex index = this->categoriesModel->index(row);
    this->ui->listViewCategories->setCurrentIndex(index);
    this->ui->listViewCategories->edit(index);

    this->updateWidgets();
}

void DialogAnnotation::slot_insertLabelPressed()
{
    std::cout << "void DialogAnnotation::slot_insertLabelPressed()" << std::endl;

    int row = this->labelsModel->rowCount();
    this->labelsModel->insertRows(row, 1);

    QModelIndex index = this->labelsModel->index(row);
    this->ui->listViewLabels->setCurrentIndex(index);
    this->ui->listViewLabels->edit(index);

    this->updateWidgets();
}

void DialogAnnotation::slot_removeCategoryPressed()
{
    int rowL = this->labelsModel->rowCount();
    this->labelsModel->removeRows(0, rowL);

    int rowC = this->ui->listViewCategories->currentIndex().row();
    this->categoriesModel->removeRows(rowC, 1);
    this->updateWidgets();
}

void DialogAnnotation::slot_removeLabelPressed()
{
    int rowL = this->ui->listViewLabels->currentIndex().row();
    this->labelsModel->removeRows(rowL, 1);
    this->updateWidgets();
}
