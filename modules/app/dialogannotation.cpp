#include "dialogannotation.h"
#include "ui_dialogannotation.h"

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);

    this->ui->treeWidgetAttributes->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                                    QAbstractItemView::DoubleClicked);
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

void DialogAnnotation::slot_initializeDialog()
{

}
