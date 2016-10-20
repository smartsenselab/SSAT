#include "dialogannotation.h"
#include "ui_dialogannotation.h"

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);

    this->ui->listViewCategories->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                                    QAbstractItemView::DoubleClicked);
    this->ui->listViewLabels->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                                    QAbstractItemView::DoubleClicked);

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

    this->connect(this->ui->pushButtonRemoveRow,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_removeRowPressed())
                  );
}

DialogAnnotation::~DialogAnnotation()
{
    delete ui;
}

void DialogAnnotation::insertCategory(QTreeWidgetItem *parent, string _name)
{

}

void DialogAnnotation::insertLabel(string _name)
{

}

void DialogAnnotation::removeRow()
{

}

void DialogAnnotation::updateActions()
{

}

void DialogAnnotation::slot_initializeDialog()
{

}

void DialogAnnotation::slot_insertCategoryPressed()
{
    std::cout << "void DialogAnnotation::slot_insertCategoryPressed()" << std::endl;
}

void DialogAnnotation::slot_insertLabelPressed()
{
    std::cout << "void DialogAnnotation::slot_insertLabelPressed()" << std::endl;
}

void DialogAnnotation::slot_removeRowPressed()
{
    std::cout << "void DialogAnnotation::slot_removeRowPressed()" << std::endl;

}
