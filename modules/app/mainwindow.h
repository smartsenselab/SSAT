#ifndef mainwindow_h
#define mainwindow_h

#include <QFileDialog>
#include <QMainWindow>
#include <QScopedPointer>

#include "videomanager.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QScopedPointer<Ui::MainWindow> ui;

    bool loaded;
    double totalFrames;
    VideoManager *manager;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:
    void openFile();
    void slideVideo(double _frame);
};

#endif
