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
    this->connect(this->ui->comboBoxCategory,
                  SIGNAL(activated(QString)),
                  this,
                  SLOT(slot_comboBoxCategoryActivated(QString))
                  );

    this->connect(this->ui->lineEditName,
                  SIGNAL(textChanged(QString)),
                  this,
                  SLOT(slot_textChanged())
                  );

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
                  SLOT(slot_buttonBoxAccepted())
                  );

    this->connect(this->ui->buttonBox,
                  SIGNAL(rejected()),
                  this,
                  SLOT(slot_buttonBoxRejected())
                  );

    this->connect(this->ui->spinBoxInitialFrame,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_valueChanged())
                  );

    this->connect(this->ui->spinBoxFinalFrame,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_valueChanged())
                  );
}

void DialogFrameBased::initializeComboboxes()
{
    QStringList categoryList, labelList;
    QSet<QString> categorySet, labelSet;

    // populate comboBoxCategory
    multimap<string, string>::iterator it;
    for(it = this->singleton->attributes.begin(); it != this->singleton->attributes.end(); it++)
    {
        categorySet.insert(QString::fromStdString(it->first));
    }
    categoryList.append(categorySet.toList());

    this->categoryModel = new QStringListModel(this);
    this->categoryModel->setStringList(categoryList);
    this->ui->comboBoxCategory->setModel(this->categoryModel);

    // populate comboBoxLabel
    string category = this->ui->comboBoxCategory->currentText().toStdString();
    for(it = this->singleton->attributes.lower_bound(category); it != this->singleton->attributes.upper_bound(category); it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel = new QStringListModel(this);
    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);

    this->ui->buttonBox->setEnabled(false);
    this->nameFlag = 0;
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

    this->initializeComboboxes();
}

void DialogFrameBased::slot_comboBoxCategoryActivated(const QString &_text)
{
    QStringList labelList;
    QSet<QString> labelSet;

    // populate comboBoxLabel
    string category = _text.toStdString();
    multimap<string, string>::iterator it;
    for(it = this->singleton->attributes.lower_bound(category); it != this->singleton->attributes.upper_bound(category); it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);
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

void DialogFrameBased::slot_valueChanged(){

    int InitFrame = IniFrameValue();
    int FinalFrame = EndFrameValue();

    if(InitFrame >= FinalFrame || this->nameFlag == 0){
        this->ui->buttonBox->setEnabled(false);
    }
    else if( InitFrame < FinalFrame && this->nameFlag == 1){
        this->ui->buttonBox->setEnabled(true);
    }
}

void DialogFrameBased::slot_buttonBoxAccepted()
{
    FrameBasedData data = FrameBasedData(this->ui->spinBoxInitialFrame->value(),
                                         this->ui->spinBoxFinalFrame->value(),
                                         this->ui->comboBoxCategory->currentText().toStdString(),
                                         this->ui->comboBoxLabel->currentText().toStdString(),
                                         this->ui->lineEditName->text().toStdString());
    emit this->signal_frameBasedAccepted(data);
    this->accept();
}

void DialogFrameBased::slot_textChanged(){

    int InitFrame = IniFrameValue();
    int EndFrame = EndFrameValue();

    QString name2 = NameValue();
    if(name2.length() == 0  && EndFrame <= InitFrame ){
        this->nameFlag = 0;
        this->ui->buttonBox->setEnabled(false);
    }
    else if( name2.length() != 0 && EndFrame > InitFrame ){
        this->ui->buttonBox->setEnabled(true);
        this->nameFlag = 1;
    }
    else if(name2.length() == 0 && EndFrame > InitFrame ){
        this->nameFlag = 0;
        this->ui->buttonBox->setEnabled(false);
    }
    else if(name2.length() != 0 && EndFrame <= InitFrame ){
        this->nameFlag = 1;
        this->ui->buttonBox->setEnabled(false);
    }
}


void DialogFrameBased::slot_buttonBoxRejected()
{
    this->reject();
}
