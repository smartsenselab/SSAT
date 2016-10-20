#include "dialogannotation.h"
#include "ui_dialogannotation.h"

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);

    this->connectSignalSlots();
    this->enableWidgets(false);

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
    this->ui->pushButtonInsertCategory->setEnabled(_enable);
    this->ui->pushButtonInsertLabel->setEnabled(_enable);
    this->ui->pushButtonRemoveCategory->setEnabled(_enable);
    this->ui->pushButtonRemoveLabel->setEnabled(_enable);
}

void DialogAnnotation::slot_initializeDialog(Core &_singleton)
{
    std::cout << "void DialogAnnotation::slot_initializeDialog()" << std::endl;
    QMultiMap<QString, QString> qAttributes;

    multimap<string, string>::iterator it;
    for(it = _singleton.attributes.begin(); it != _singleton.attributes.end(); it++)
    {
        qAttributes.insert(QString::fromStdString(it->first), QString::fromStdString(it->second));
    }

    QStringList categories(qAttributes.uniqueKeys());

    this->categoriesModel = new QStringListModel(this);
    this->categoriesModel->setStringList(categories);
    this->ui->listViewCategories->setModel(this->categoriesModel);
}

void DialogAnnotation::slot_listViewCategoriesClicked(QModelIndex _index)
{
    std::cout << "void DialogAnnotation::slot_listViewCategoriesClicked()" << std::endl;
}

void DialogAnnotation::slot_listViewLabelsClicked(QModelIndex _index)
{
    std::cout << "void DialogAnnotation::slot_listViewLabelsClicked()" << std::endl;
}

void DialogAnnotation::slot_insertCategoryPressed()
{
    std::cout << "void DialogAnnotation::slot_insertCategoryPressed()" << std::endl;
}

void DialogAnnotation::slot_insertLabelPressed()
{
    std::cout << "void DialogAnnotation::slot_insertLabelPressed()" << std::endl;
}

void DialogAnnotation::slot_removeCategoryPressed()
{
    std::cout << "void DialogAnnotation::slot_removeCategoryPressed()" << std::endl;
}

void DialogAnnotation::slot_removeLabelPressed()
{
    std::cout << "void DialogAnnotation::slot_removeLabelPressed()" << std::endl;
}
