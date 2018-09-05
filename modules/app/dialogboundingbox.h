#ifndef DIALOGBOUNDINGBOX_H
#define DIALOGBOUNDINGBOX_H

#include <QDialog>
#include <QMessageBox>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QtCore>
#include <QtGui>

#include "boundingbox.h"
#include "core.h"
#include "treemodelcompleter.h"

namespace Ui
{
class DialogBoundingBox;
}

class DialogBoundingBox : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogBoundingBox *ui;

    unsigned int bboxKey;
    unsigned int frameId;
    unsigned int maxId;

    QStandardItemModel* qStandardModel = NULL;
    TreeModelCompleter *qTreeCompleter = NULL;

    QStringListModel *categoryModel = NULL;
    QStringListModel *labelModel = NULL;

    Core *singleton = NULL;

public:
    explicit DialogBoundingBox(QWidget *parent = 0);
    ~DialogBoundingBox();

private:
    ///
    /// \brief connectSignalSlots connect button signals to their slots
    ///
    void connectSignalSlots();

    ///
    /// \brief initializeComboboxes Build the multimap of the category and label
    ///
    void initializeComboboxes();

    ///
    /// \brief initializeComboboxes Add a new category
    /// \param _category    The QString (name) that will represent the category
    ///
    void initializeComboboxes(const QString _category);

    ///
    /// \brief stlToModel
    /// \param _nodeAtt
    /// \param _qParentItem
    ///
    void stlToModel(Attribute* _nodeAtt, QStandardItem* _qParentItem);

public slots:
    ///
    /// \brief slot_initializeDialog Load information from core and initialize fields
    /// \param _singleton Core
    /// \param _bbox
    ///
    void slot_initializeDialog(Core &_core, const unsigned int _frameId, const unsigned int _bboxKey);

    ///
    /// \brief slot_comboBoxCategoryActivated   Insert a new category
    /// \param _text
    ///
    void slot_comboBoxCategoryActivated(const QString &_text);

    ///
    /// \brief slot_spinBoxIdChanged Changing bounding bod id check
    ///
    void slot_spinBoxIdChanged(int _value);

    ///
    /// \brief slot_buttonBoxAccepted Insert or Change bounding box succeed
    ///
    void slot_buttonBoxAccepted();

    ///
    /// \brief slot_buttonBoxRejected Insert or Change bounding box canceled
    ///
    void slot_buttonBoxRejected();

signals:
    ///
    /// \brief signal_updateFrame Signal to call MainWindows::slot_updateFrame
    ///
    void signal_updateFrame();
};

#endif // DIALOGBOUNDINGBOX_H
