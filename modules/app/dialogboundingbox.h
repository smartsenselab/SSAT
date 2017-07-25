#ifndef DIALOGBOUNDINGBOX_H
#define DIALOGBOUNDINGBOX_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

#include "boundingbox.h"

namespace Ui
{
class DialogBoundingBox;
}

class DialogBoundingBox : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogBoundingBox *ui;

public:
    explicit DialogBoundingBox(QWidget *parent = 0);
    ~DialogBoundingBox();

private:
    ///
    /// \brief connectSignalSlots connect button signals to their slots
    ///
    void connectSignalSlots();

public slots:
    ///
    /// \brief slot_initializeDialog Load information from core and initialize fields
    /// \param _singleton Core
    ///
    void slot_initializeDialog(BoundingBox &_bbox);
};

#endif // DIALOGBOUNDINGBOX_H
