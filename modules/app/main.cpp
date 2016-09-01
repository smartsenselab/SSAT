#include <QApplication>
#include "mainwindow.h"

#include <QCoreApplication>

#include <stdlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <core.h>

int main(int argc, char *argv[])
{

    teste(100);

    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
