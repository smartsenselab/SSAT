#include "dialogannotation.h"
#include "ui_dialogannotation.h"

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);
}

DialogAnnotation::~DialogAnnotation()
{
    delete ui;
}

void DialogAnnotation::insertChild(QTreeWidgetItem *parent, string _name)
{

}

void DialogAnnotation::insertRow(string _name)
{

}

void DialogAnnotation::removeRow()
{

}
