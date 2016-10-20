#ifndef DIALOGFRAMEBASED_H
#define DIALOGFRAMEBASED_H

#include <iostream>

#include <QDialog>

namespace Ui {
    class DialogFrameBased;
}

class DialogFrameBased : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogFrameBased *ui;

    int frameId, totalFrames;

public:
    explicit DialogFrameBased(QWidget *parent = 0);
    ~DialogFrameBased();
    int IniFrameValue();
    int EndFrameValue();
    QString NameValue();

private:
    void connectSignalSlots();

public slots:
    void slot_initializeDialog(int _totalFrames, int _frameId);

    void slot_rewindButtonPressed();
    void slot_backButtonPressed();
    void slot_forwardButtonPressed();
    void slot_fastfButtonPressed();
    void slot_ButtonBoxAccepted();
    void slot_ButtonBoxRejected();

signals:
    void signal_rewindButtonPressed();
    void signal_backButtonPressed();
    void signal_forwardButtonPressed();
    void signal_fastfButtonPressed();
    void signal_ButtonBoxAccepted();

};

#endif // DIALOGFRAMEBASED_H
