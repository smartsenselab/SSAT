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
    headers << tr("Attributes");
    TreeModel *model = new TreeModel(headers, "Object Recognition\n\tRafael\n\tHenrique");

    this->ui->treeViewAttributes->setModel(model);

    this->connect(this->ui->pushButtonInsertCategory,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_insertCategoryPressed())
                  );

    this->connect(this->ui->pushButtonInsertLabel,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_insertLabelPressed())
                  );

    this->connect(this->ui->pushButtonRemoveRow,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_removeRowPressed())
                  );
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

void DialogAnnotation::updateActions()
{
    bool hasSelection = !this->ui->treeViewAttributes->selectionModel()->selection().isEmpty();
    bool hasCurrent = this->ui->treeViewAttributes->selectionModel()->currentIndex().isValid();

    if (hasCurrent) {
        this->ui->treeViewAttributes->closePersistentEditor(this->ui->treeViewAttributes->selectionModel()->currentIndex());

//        int row = this->ui->treeViewAttributes->selectionModel()->currentIndex().row();
//        int column = this->ui->treeViewAttributes->selectionModel()->currentIndex().column();
//        if (this->ui->treeViewAttributes->selectionModel()->currentIndex().parent().isValid())
//            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
//        else
//            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}

void DialogAnnotation::slot_initializeDialog()
{

}

void DialogAnnotation::slot_insertCategoryPressed()
{
//    std::cout << "void DialogAnnotation::slot_insertCategoryPressed()" << std::endl;

    QModelIndex index = this->ui->treeViewAttributes->selectionModel()->currentIndex();
    QAbstractItemModel *model = this->ui->treeViewAttributes->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"), Qt::EditRole);
    }

    this->ui->treeViewAttributes->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

void DialogAnnotation::slot_insertLabelPressed()
{
//    std::cout << "void DialogAnnotation::slot_insertLabelPressed()" << std::endl;

    QModelIndex index = this->ui->treeViewAttributes->selectionModel()->currentIndex();
    QAbstractItemModel *model = this->ui->treeViewAttributes->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}

void DialogAnnotation::slot_removeRowPressed()
{
//    std::cout << "void DialogAnnotation::slot_removeRowPressed()" << std::endl;

    QModelIndex index = this->ui->treeViewAttributes->selectionModel()->currentIndex();
    QAbstractItemModel *model = this->ui->treeViewAttributes->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}
