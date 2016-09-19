#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    this->loaded = false;
    this->manager = new VideoManager;

    this->connect(ui->actionOpen,
                  &QAction::triggered,
                  this,
                  &MainWindow::openFile);

    this->connect(ui->sliderFrame,
                  SIGNAL(sliderMoved(int)),
                  this,
                  SLOT(slideVideo(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::openFile()
{
    QString videoName = QFileDialog::getOpenFileName(this,
                                                     tr("Open Video..."),
                                                     tr("/home"),
                                                     tr("Video Files (*.avi *.mp4 *.mov)"));
    this->manager->loadVideo(videoName);

    this->loaded = true;
    this->totalFrames = this->manager->getTotalFrames() - 1;

    this->ui->sliderFrame->setRange(0, static_cast<int>(this->totalFrames));
    this->ui->labelFrameId->setText(QString::number(0) + "/" + QString::number(this->totalFrames));
}

void MainWindow::slideVideo(int _frame)
{
    double dFrame = static_cast<double>(_frame);
    std::cout << _frame << std::endl;

    Mat frameMat = this->manager->getFrame(dFrame);
    QImage frameQImage = this->manager->matToQimage(frameMat);

    this->ui->labelFrameShow->setPixmap(QPixmap::fromImage(frameQImage));
    this->ui->labelFrameId->setText(QString::number(_frame) + "/" + QString::number(this->totalFrames));
}
