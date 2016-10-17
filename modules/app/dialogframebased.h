#ifndef DIALOGFRAMEBASED_H
#define DIALOGFRAMEBASED_H

#include <QDialog>

//#include "mainwindow.h"

namespace Ui {
    class DialogFrameBased;
}

class DialogFrameBased : public QDialog
{
    Q_OBJECT

private:
    Ui::DialogFrameBased *ui;

    QMainWindow *typedParent = NULL;
    int totalFrames;

public:
    explicit DialogFrameBased(QWidget *parent = 0);
    ~DialogFrameBased();

private:
    void connectSignalSlots();

public slots:
    void slot_initializeDialog(int _totalFrames, int _frameId);

    void slot_rewindButton();
    void slot_backButton();
    void slot_forwardButton();
    void slot_fastfButton();
};

#endif // DIALOGFRAMEBASED_H
