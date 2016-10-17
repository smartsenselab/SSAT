#include "dialogframebased.h"
#include "ui_dialogframebased.h"

DialogFrameBased::DialogFrameBased(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFrameBased)
{
    ui->setupUi(this);
}

DialogFrameBased::~DialogFrameBased()
{
    delete ui;
}
