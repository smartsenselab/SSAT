#include "dialogannotation.h"
#include "ui_dialogannotation.h"

DialogAnnotation::DialogAnnotation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAnnotation)
{
    ui->setupUi(this);

    this->ui->treeViewAttributes->setEditTriggers(QAbstractItemView::AnyKeyPressed |
                                                    QAbstractItemView::DoubleClicked);

    QStringList headers;


//    TreeModel *model = new TreeModel(headers, file.readAll());
//    this->ui->treeViewAttributes->setModel();
}

DialogAnnotation::~DialogAnnotation()
{
    delete ui;
}

void DialogAnnotation::insertCategory(QTreeWidgetItem *parent, string _name)
{

}

void DialogAnnotation::insertLabel(string _name)
{

}

void DialogAnnotation::removeRow()
{

}

void DialogAnnotation::slot_initializeDialog()
{

}

void DialogAnnotation::slot_insertChild()
{

}

bool DialogAnnotation::slot_insertColumn()
{

}

void DialogAnnotation::slot_insertRow()
{

}

bool DialogAnnotation::slot_removeColumn()
{

}

void DialogAnnotation::slot_removeRow()
{

}
