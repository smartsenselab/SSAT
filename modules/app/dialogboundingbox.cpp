#include "dialogboundingbox.h"
#include "ui_dialogboundingbox.h"

DialogBoundingBox::DialogBoundingBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBoundingBox)
{
    this->ui->setupUi(this);
    this->ui->buttonTracker->setEnabled(false);
}

DialogBoundingBox::~DialogBoundingBox()
{
    delete ui;
}

void DialogBoundingBox::connectSignalSlots()
{

}

void DialogBoundingBox::slot_initializeDialog(BoundingBox &_bbox)
{

}
