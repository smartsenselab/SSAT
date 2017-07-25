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
}

void DialogBoundingBox::initializeComboboxes(const QString _category)
{
    QStringList categoryList, labelList;
    QSet<QString> categorySet, labelSet;
    string category = _category.toStdString();

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
    for(it = this->singleton->attributes.lower_bound(category); it != this->singleton->attributes.upper_bound(category); it++)
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

    this->initializeComboboxes();
}
