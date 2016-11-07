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

int DialogFrameBased::IniFrameValue()
{
    return this->ui->spinBoxInitialFrame->value();
}

int DialogFrameBased::EndFrameValue()
{
    return this->ui->spinBoxFinalFrame->value();
}

QString DialogFrameBased::NameValue()
{
    return this->ui->lineEditName->text();
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

void DialogFrameBased::slot_initializeDialog(Core &_singleton, const int _totalFrames, const int _frameId)
{
    this->frameId = _frameId - 1;
    this->singleton = &_singleton;
    this->totalFrames = _totalFrames;

    this->ui->spinBoxInitialFrame->setMinimum(1);
    this->ui->spinBoxInitialFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxInitialFrame->setValue(_frameId - 1);

    this->ui->spinBoxFinalFrame->setMinimum(1);
    this->ui->spinBoxFinalFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxFinalFrame->setValue(_frameId - 1);

}

void DialogFrameBased::slot_comboBoxCategoryActivated()
{

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

void DialogFrameBased::slot_buttonBoxAccepted(){
    emit this->signal_buttonBoxAccepted();
    this->accept();
}

void DialogFrameBased::slot_buttonBoxRejected(){
    this->reject();
}

void DialogFrameBased::slot_accept()
{
    FrameBasedData data = FrameBasedData(this->ui->spinBoxInitialFrame->value(),
                                         this->ui->spinBoxFinalFrame->value(),
                                         this->ui->comboBoxCategory->currentText().toStdString(),
                                         this->ui->comboBoxLabel->currentText().toStdString(),
                                         this->ui->lineEditName->text().toStdString());
    emit this->signal_frameBasedOkButtonPressed(data);
    this->accept();
}

void DialogFrameBased::slot_reject()
{
    this->reject();
}
