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
    this->connect(this->ui->comboBoxCategory,
                  SIGNAL(activated(QString)),
                  this,
                  SLOT(slot_comboBoxCategoryActivated(QString))
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
    BoundingBox bbox = this->singleton->frames[this->frameId].getBox(this->bboxKey);

    if(bbox.getId() != 0)
    {
        this->ui->comboBoxCategory->setCurrentText(QString::fromStdString(bbox.getCategory()));
        emit this->ui->comboBoxCategory->activated(QString::fromStdString(bbox.getCategory()));
        this->ui->comboBoxLabel->setCurrentText(QString::fromStdString(bbox.getLabel()));
        this->ui->spinBoxId->setValue(bbox.getId());
    }
    else
    {
        // Alterar aqui
        this->ui->comboBoxCategory->setCurrentText(QString::fromStdString(bbox.getCategory()));
        this->ui->comboBoxLabel->setCurrentText(QString::fromStdString(bbox.getLabel()));
        this->ui->spinBoxId->setValue(bbox.getId());
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
    for(it = this->singleton->attributes.lower_bound(category); it != this->singleton->attributes.upper_bound(category); it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);
}
