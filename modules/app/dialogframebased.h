#ifndef DIALOGFRAMEBASED_H
#define DIALOGFRAMEBASED_H

#include <cmath>
#include <iostream>

#include <QDialog>

#include "core.h"
#include "framebaseddata.h"

namespace Ui {
    class DialogFrameBased;
}

class DialogFrameBased : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogFrameBased *ui;

    int frameId, totalFrames;

    Core *singleton = NULL;

public:
    explicit DialogFrameBased(QWidget *parent = 0);
    ~DialogFrameBased();
    int IniFrameValue();
    int EndFrameValue();
    QString NameValue();

private:
    void connectSignalSlots();

public slots:
    void slot_initializeDialog(const int _totalFrames, const int _frameId);

    void slot_rewindButtonPressed();
    void slot_backButtonPressed();
    void slot_forwardButtonPressed();
    void slot_fastfButtonPressed();
    void slot_ButtonBoxAccepted();
    void slot_ButtonBoxRejected();

    void slot_accept();
    void slot_reject();

signals:
    void signal_rewindButtonPressed();
    void signal_backButtonPressed();
    void signal_forwardButtonPressed();
    void signal_fastfButtonPressed();
    void signal_ButtonBoxAccepted();

    void signal_frameBasedOkButtonPressed(const FrameBasedData _data);
    void signal_frameBasedCancelButtonPressed();
};

#endif // DIALOGFRAMEBASED_H
