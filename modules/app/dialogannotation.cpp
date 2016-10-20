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
