#include <QApplication>
#include "mainwindow.h"

#include <QCoreApplication>

#include <stdlib.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char *argv[])
{
    /*
     * Category* [combobox]
     * Label* [combobox]
     * Name [linetext]
     */

    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
