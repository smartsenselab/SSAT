#ifndef mainwindow_h
#define mainwindow_h

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
    VideoManager *manager;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

public slots:
//    bool openFile();
//    bool slideVideo(double _frame);
};

#endif
