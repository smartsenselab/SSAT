#include "dialogframebased.h"
#include "ui_dialogframebased.h"

DialogFrameBased::DialogFrameBased(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogFrameBased)
{
    ui->setupUi(this);

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
}

void DialogFrameBased::slot_initializeDialog(int _totalFrames, int _frameId)
{
    this->totalFrames = _totalFrames;

    this->ui->spinBoxInitialFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxInitialFrame->setValue(_frameId - 1);
    this->ui->spinBoxFinalFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxFinalFrame->setValue(_frameId);
}

void DialogFrameBased::slot_rewindButtonPressed()
{
    std::cout << "emit this->signal_rewindButtonPressed();" << std::endl;
    emit this->signal_rewindButtonPressed();
}

void DialogFrameBased::slot_backButtonPressed()
{
    std::cout << "emit this->signal_backButtonPressed();" << std::endl;
    emit this->signal_backButtonPressed();
}

void DialogFrameBased::slot_forwardButtonPressed()
{
    std::cout << "emit this->signal_forwardButtonPressed();" << std::endl;
    emit this->signal_forwardButtonPressed();
}

void DialogFrameBased::slot_fastfButtonPressed()
{
    std::cout << "emit this->signal_fastfButtonPressed();" << std::endl;
    emit this->signal_fastfButtonPressed();
}
