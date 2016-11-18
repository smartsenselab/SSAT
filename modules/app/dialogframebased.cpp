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
    delete this->ui;
}

int DialogFrameBased::getIniFrameValue()
{
    return this->ui->spinBoxInitialFrame->value();
}

int DialogFrameBased::getEndFrameValue()
{
    return this->ui->spinBoxFinalFrame->value();
}

QString DialogFrameBased::getNameValue()
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
                  SLOT(slot_lineEditNameChanged())
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
                  SLOT(slot_spinBoxValueChanged())
                  );

    this->connect(this->ui->spinBoxFinalFrame,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_spinBoxValueChanged())
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
}

void DialogFrameBased::slot_initializeDialog(Core &_singleton, const int _frameId)
{
    this->frameId = _frameId - 1;
    this->nameFlag = 0;
    this->singleton = &_singleton;
    this->totalFrames = this->singleton->frames.size();

    this->ui->buttonBox->setEnabled(false);

    this->ui->spinBoxInitialFrame->setMinimum(1);
    this->ui->spinBoxInitialFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxInitialFrame->setValue(this->frameId);

    this->ui->spinBoxFinalFrame->setMinimum(1);
    this->ui->spinBoxFinalFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxFinalFrame->setValue(this->frameId);

    this->initializeComboboxes();
}

void DialogFrameBased::slot_initializeDialog(Core &_singleton, const QModelIndex _index)
{
    this->nameFlag = 0;
    this->singleton = &_singleton;
    this->totalFrames = this->singleton->frames.size();

    FrameBasedData frameData = this->singleton->frameData.at(_index.row());

    this->ui->spinBoxInitialFrame->setMinimum(1);
    this->ui->spinBoxInitialFrame->setMaximum(this->totalFrames);
    this->ui->spinBoxFinalFrame->setMinimum(1);
    this->ui->spinBoxFinalFrame->setMaximum(this->totalFrames);

    this->initializeComboboxes();

    this->ui->lineEditName->setText(QString::fromStdString(frameData.getName()));
    this->ui->comboBoxLabel->setCurrentText(QString::fromStdString(frameData.getLabel()));
    this->ui->comboBoxCategory->setCurrentText(QString::fromStdString(frameData.getCategory()));
    this->ui->spinBoxInitialFrame->setValue(frameData.getInitialFrameId());
    this->ui->spinBoxFinalFrame->setValue(frameData.getFinalFrameId());
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

void DialogFrameBased::slot_spinBoxValueChanged()
{
    int initFrame = this->getIniFrameValue();
    int finalFrame = this->getEndFrameValue();

    // this->ui->spinBoxInitialFrame->setMaximum(finalFrame);
    // this->ui->spinBoxFinalFrame->setMaximum(initFrame);

    if(initFrame >= finalFrame || this->nameFlag == 0)
    {
        this->ui->buttonBox->setEnabled(false);
    }
    else if( initFrame < finalFrame && this->nameFlag == 1)
    {
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

void DialogFrameBased::slot_lineEditNameChanged()
{

    int initFrame = this->getIniFrameValue();
    int endFrame = this->getEndFrameValue();

    QString name2 = this->getNameValue();
    if(name2.length() == 0  && endFrame <= initFrame)
    {
        this->nameFlag = 0;
        this->ui->buttonBox->setEnabled(false);
    }
    else if( name2.length() != 0 && endFrame > initFrame)
    {
        this->ui->buttonBox->setEnabled(true);
        this->nameFlag = 1;
    }
    else if(name2.length() == 0 && endFrame > initFrame)
    {
        this->nameFlag = 0;
        this->ui->buttonBox->setEnabled(false);
    }
    else if(name2.length() != 0 && endFrame <= initFrame)
    {
        this->nameFlag = 1;
        this->ui->buttonBox->setEnabled(false);
    }
}


void DialogFrameBased::slot_buttonBoxRejected()
{
    this->reject();
}
