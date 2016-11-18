#ifndef DIALOGFRAMEBASED_H
#define DIALOGFRAMEBASED_H

#include <cmath>
#include <iostream>

#include <QDialog>
#include <QtCore>
#include <QtGui>

#include "core.h"
#include "framebaseddata.h"

namespace Ui {
    class DialogFrameBased;
}

class DialogFrameBased : public QDialog
{
    Q_OBJECT

private:
    int nameFlag;

    Ui::DialogFrameBased *ui;

    int frameId, totalFrames;
    Core *singleton = NULL;

    QStringListModel *categoryModel = NULL;
    QStringListModel *labelModel = NULL;

public:
    explicit DialogFrameBased(QWidget *parent = 0);
    ~DialogFrameBased();
    int getIniFrameValue();
    int getEndFrameValue();
    QString getNameValue();

private:
    void connectSignalSlots();
    void initializeComboboxes();

public slots:
    void slot_initializeDialog(Core &_singleton, const int _frameId);
    void slot_initializeDialog(Core &_singleton, const QModelIndex _index);
    void slot_comboBoxCategoryActivated(const QString &_text);

    void slot_rewindButtonPressed();
    void slot_backButtonPressed();
    void slot_forwardButtonPressed();
    void slot_fastfButtonPressed();
    void slot_buttonBoxAccepted();
    void slot_buttonBoxRejected();
    void slot_spinBoxValueChanged();
    void slot_lineEditNameChanged();

signals:
    void signal_rewindButtonPressed();
    void signal_backButtonPressed();
    void signal_forwardButtonPressed();
    void signal_fastfButtonPressed();
    void signal_buttonBoxAccepted();

    void signal_frameBasedAccepted(const FrameBasedData _data);
    void signal_frameBasedRejected();
};

#endif // DIALOGFRAMEBASED_H
