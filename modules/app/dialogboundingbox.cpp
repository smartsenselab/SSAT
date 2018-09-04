#include "dialogboundingbox.h"
#include "ui_dialogboundingbox.h"

DialogBoundingBox::DialogBoundingBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogBoundingBox)
{
    this->ui->setupUi(this);
    this->ui->buttonTracker->setEnabled(false);
    this->setFixedSize(this->width(), this->height());
}

DialogBoundingBox::~DialogBoundingBox()
{
    delete ui;
}

void DialogBoundingBox::connectSignalSlots()
{
    this->connect(this->ui->comboBoxCategory,
                  SIGNAL(activated(QString)),
                  this,
                  SLOT(slot_comboBoxCategoryActivated(QString))
                  );

    this->connect(this->ui->spinBoxId,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_spinBoxIdChanged(int))
                  );

    this->connect(this->ui->buttonBoxOKcancel,
                  SIGNAL(accepted()),
                  this,
                  SLOT(slot_buttonBoxAccepted())
                  );

    this->connect(this->ui->buttonBoxOKcancel,
                  SIGNAL(rejected()),
                  this,
                  SLOT(slot_buttonBoxRejected())
                  );
}

void DialogBoundingBox::initializeComboboxes()
{
    QStringList categoryList, labelList;
    QSet<QString> categorySet, labelSet;

    // populate comboBoxCategory
    multimap<string, string>::iterator it;
    for(it = this->singleton->attributes.begin();
        it != this->singleton->attributes.end();
        it++)
    {
        categorySet.insert(QString::fromStdString(it->first));
    }
    categoryList.append(categorySet.toList());

    this->categoryModel = new QStringListModel(this);
    this->categoryModel->setStringList(categoryList);
    this->ui->comboBoxCategory->setModel(this->categoryModel);

    // populate comboBoxLabel
    string category = this->ui->comboBoxCategory->currentText().toStdString();
    for(it = this->singleton->attributes.lower_bound(category);
        it != this->singleton->attributes.upper_bound(category);
        it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel = new QStringListModel(this);
    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);

    // change widgets values
    BoundingBox bbox = this->singleton->frames[this->frameId].getBoxByKey(this->bboxKey);

    this->ui->spinBoxId->setMinimum(1);
    this->ui->spinBoxId->setMaximum(100000);

    // populate combobox and spinbox
    if(bbox.getId() > 0)
    {
        this->ui->comboBoxCategory->setCurrentText(QString::fromStdString(bbox.getCategory()));
        emit this->ui->comboBoxCategory->activated(QString::fromStdString(bbox.getCategory()));
        this->ui->comboBoxLabel->setCurrentText(QString::fromStdString(bbox.getLabel()));
        this->ui->spinBoxId->setValue(bbox.getId());
    }
    else
    {
        unsigned int idValue = this->singleton->frames[this->frameId].getBoxes().size();

        if(this->singleton->setup.getLatestCategory().empty())
        {
            this->ui->comboBoxCategory->setCurrentIndex(0);
            emit this->ui->comboBoxCategory->activated(0);
            this->ui->comboBoxLabel->setCurrentIndex(0);
            this->ui->spinBoxId->setValue(idValue);
        }
        else
        {
            this->ui->comboBoxCategory->setCurrentText(QString::fromStdString(this->singleton->setup.getLatestCategory()));
            emit this->ui->comboBoxCategory->activated(QString::fromStdString(this->singleton->setup.getLatestCategory()));
            this->ui->comboBoxLabel->setCurrentText(QString::fromStdString(this->singleton->setup.getLatestLabel()));
            this->ui->spinBoxId->setValue(this->singleton->setup.getLatestId());
        }
    }

    this->ui->spinBoxX->setValue(bbox.getX());
    this->ui->spinBoxY->setValue(bbox.getY());
    this->ui->spinBoxW->setValue(bbox.getW());
    this->ui->spinBoxH->setValue(bbox.getH());

    this->ui->lineEditInfo->setText(QString::fromStdString(bbox.getInfo()));
}

void DialogBoundingBox::initializeComboboxes(const QString _category)
{
    QStringList categoryList, labelList;
    QSet<QString> categorySet, labelSet;
    string category = _category.toStdString();

    // populate comboBoxCategory
    multimap<string, string>::iterator it;
    for(it = this->singleton->attributes.begin();
        it != this->singleton->attributes.end();
        it++)
    {
        categorySet.insert(QString::fromStdString(it->first));
    }
    categoryList.append(categorySet.toList());

    this->categoryModel = new QStringListModel(this);
    this->categoryModel->setStringList(categoryList);
    this->ui->comboBoxCategory->setModel(this->categoryModel);

    // populate comboBoxLabel
    for(it = this->singleton->attributes.lower_bound(category);
        it != this->singleton->attributes.upper_bound(category);
        it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel = new QStringListModel(this);
    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);
}

void DialogBoundingBox::slot_initializeDialog(Core &_core, const unsigned int _frameId, const unsigned int _bboxKey)
{
    this->singleton = &_core;

    this->bboxKey = _bboxKey;
    this->frameId = _frameId;

    this->connectSignalSlots();
    this->initializeComboboxes();
}

void DialogBoundingBox::slot_comboBoxCategoryActivated(const QString &_text)
{
    QStringList labelList;
    QSet<QString> labelSet;

    // populate comboBoxLabel
    string category = _text.toStdString();
    multimap<string, string>::iterator it;
    for(it = this->singleton->attributes.lower_bound(category);
        it != this->singleton->attributes.upper_bound(category);
        it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);
}

void DialogBoundingBox::slot_spinBoxIdChanged(int _value)
{
    BoundingBox bbox = this->singleton->frames[this->frameId].getBoxById(_value);
    if(bbox.isValid() && (this->bboxKey != bbox.getKey()))
    {
        this->ui->buttonBoxOKcancel->setEnabled(false);
    }
    else
    {
        this->ui->buttonBoxOKcancel->setEnabled(true);
    }
}

void DialogBoundingBox::slot_buttonBoxAccepted()
{
    BoundingBox bbox = BoundingBox(this->ui->spinBoxId->value(),
                                   this->bboxKey,
                                   this->ui->comboBoxCategory->currentText().toStdString(),
                                   this->ui->lineEditInfo->text().toStdString(),
                                   this->ui->comboBoxLabel->currentText().toStdString(),
                                   std::string(),
                                   this->ui->spinBoxX->value(),
                                   this->ui->spinBoxY->value(),
                                   this->ui->spinBoxW->value(),
                                   this->ui->spinBoxH->value()
                                   );

    this->singleton->frames[this->frameId].setBox(this->bboxKey, bbox);

    this->singleton->setup.setLargestId(bbox.getId());
    this->singleton->setup.setLatestCategory(bbox.getCategory());
    this->singleton->setup.setLatestId(bbox.getId());
    this->singleton->setup.setLatestLabel(bbox.getLabel());

    emit this->signal_updateFrame();
    this->accept();
}

void DialogBoundingBox::slot_buttonBoxRejected()
{
    this->reject();
}
