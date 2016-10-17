#include "dialogframebased.h"
#include "ui_dialogframebased.h"

DialogFrameBased::DialogFrameBased(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFrameBased)
{
    ui->setupUi(this);
//    this->typedParent = qobject_cast<MainWindow *>(this->parent());
}

DialogFrameBased::~DialogFrameBased()
{
    delete ui;
}

void DialogFrameBased::connectSignalSlots()
{
//    this->connect(this->ui->spinBoxInitialFrame,
//                  SIGNAL(valueChanged(int)),
//                  this->typedParent,
//                  SLOT(slot_spinBoxSpeed(int))
//                  );
}

void DialogFrameBased::slot_initializeDialog(int _totalFrames, int _frameId)
{
    this->totalFrames = _totalFrames;

    this->ui->spinBoxInitialFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxInitialFrame->setValue(_frameId - 1);
    this->ui->spinBoxFinalFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxFinalFrame->setValue(_frameId);
}

void DialogFrameBased::slot_rewindButton()
{

}

void DialogFrameBased::slot_backButton()
{

}

void DialogFrameBased::slot_forwardButton()
{

}

void DialogFrameBased::slot_fastfButton()
{

}




