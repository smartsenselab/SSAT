#include "dialogsetup.h"
#include "ui_dialogsetup.h"

DialogSetup::DialogSetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSetup)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());
}

DialogSetup::~DialogSetup()
{
    delete ui;
}
