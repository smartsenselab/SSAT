#ifndef DIALOGBOUNDINGBOX_H
#define DIALOGBOUNDINGBOX_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

#include "boundingbox.h"
#include "core.h"

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

    Core *singleton = NULL;

    QStringListModel *categoryModel = NULL;
    QStringListModel *labelModel = NULL;

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

public slots:
    ///
    /// \brief slot_initializeDialog Load information from core and initialize fields
    /// \param _singleton Core
    /// \param _bbox
    ///
    void slot_initializeDialog(Core &_core, const unsigned int _frameId, const unsigned int _bboxKey);
};

#endif // DIALOGBOUNDINGBOX_H
