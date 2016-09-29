#include <QApplication>
#include "mainwindow.h"

#include <QCoreApplication>

#include <stdlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "core.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Core *singleton = Core::getInstance(2);

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
