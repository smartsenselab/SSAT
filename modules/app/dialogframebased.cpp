#include "dialogframebased.h"
#include "ui_dialogframebased.h"

DialogFrameBased::DialogFrameBased(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFrameBased)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());
    this->connectSignalSlots();
}

DialogFrameBased::~DialogFrameBased()
{
    delete ui;
}

void DialogFrameBased::connectSignalSlots()
{
    this->connect(this->ui->buttonRewindF,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_rewindButtonPressed())
                  );

    this->connect(this->ui->buttonRewind,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_backButtonPressed())
                  );

    this->connect(this->ui->buttonForward,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_forwardButtonPressed())
                  );

    this->connect(this->ui->buttonForwardF,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_fastfButtonPressed())
                  );

    this->connect(this->ui->buttonBox,
                  SIGNAL(accepted()),
                  this,
                  SLOT(slot_accept())
                  );

    this->connect(this->ui->buttonBox,
                  SIGNAL(rejected()),
                  this,
                  SLOT(slot_reject())
                  );
}

void DialogFrameBased::slot_initializeDialog(int _totalFrames, int _frameId)
{
    this->frameId = _frameId - 1;
    this->totalFrames = _totalFrames;

    this->ui->spinBoxInitialFrame->setMinimum(1);
    this->ui->spinBoxInitialFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxInitialFrame->setValue(_frameId - 1);

    this->ui->spinBoxFinalFrame->setMinimum(1);
    this->ui->spinBoxFinalFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxFinalFrame->setValue(_frameId - 1);
}

void DialogFrameBased::slot_rewindButtonPressed()
{
    int nextFrameId = static_cast<int>((this->frameId + 1) - std::round(+this->totalFrames / 100.0));
    if(nextFrameId < 1)
    {
        nextFrameId = 1;
    }

    this->frameId = nextFrameId;
    this->ui->spinBoxFinalFrame->setValue(this->frameId);
    emit this->signal_rewindButtonPressed();
}

void DialogFrameBased::slot_backButtonPressed()
{
    int nextFrameId = (this->frameId + 1) - 2;
    if(nextFrameId < 1)
    {
        nextFrameId = 1;
    }

    this->frameId = nextFrameId;
    this->ui->spinBoxFinalFrame->setValue(this->frameId);
    emit this->signal_backButtonPressed();
}

void DialogFrameBased::slot_forwardButtonPressed()
{
    int nextFrameId = (this->frameId + 1);
    if(nextFrameId > this->totalFrames)
    {
        nextFrameId = this->totalFrames;
    }

    this->frameId = nextFrameId;
    this->ui->spinBoxFinalFrame->setValue(this->frameId);
    emit this->signal_forwardButtonPressed();
}

void DialogFrameBased::slot_fastfButtonPressed()
{
    int nextFrameId = static_cast<int>((this->frameId + 1) + std::round(+this->totalFrames / 100.0));
    if(nextFrameId > this->totalFrames)
    {
        nextFrameId = this->totalFrames;
    }

    this->frameId = nextFrameId;
    this->ui->spinBoxFinalFrame->setValue(this->frameId);
    emit this->signal_fastfButtonPressed();
}

void DialogFrameBased::slot_accept()
{
    std::cout << "Pressing OK" << std::endl;
    //add code here
    this->accept();
}

void DialogFrameBased::slot_reject()
{
    std::cout << "Pressing Cancel" << std::endl;
    //add code here
    this->reject();
}
