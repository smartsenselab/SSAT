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
                  &MainWindow::slot_openFile
                  );

    this->connect(ui->sliderFrame,
                  SIGNAL(sliderMoved(int)),
                  this,
                  SLOT(slot_slideVideo(int))
                  );

    this->connect(ui->buttonPlay,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_playVideo())
                  );
}

MainWindow::~MainWindow()
{

}

void MainWindow::slot_displayFrame(const QImage _frame)
{
    if(!_frame.isNull())
    {
        this->ui->labelFrameShow->setPixmap(QPixmap::fromImage(_frame));
    }
}

void MainWindow::slot_openFile()
{
    QString videoName = QFileDialog::getOpenFileName(this,
                                                     tr("Open Video..."),
                                                     tr("/home"),
                                                     tr("Video Files (*.avi *.mp4 *.mov)"));

    this->manager->loadVideo(videoName);

    this->loaded = true;
    this->totalFrames = this->manager->getTotalFrames() - 2;

    Mat frameMat = this->manager->getFrame(0.0);
    QImage frameQImage = this->manager->matToQimage(frameMat);

    this->ui->sliderFrame->setEnabled(true);
    this->ui->sliderFrame->setRange(0, static_cast<int>(this->totalFrames));
    this->ui->labelFrameId->setText(QString::number(0) + "/" + QString::number(this->totalFrames));
    this->ui->labelFrameShow->setPixmap(QPixmap::fromImage(frameQImage));
}

void MainWindow::slot_playVideo()
{
    bool currentStatus = this->manager->isPlaying();
    this->manager->isPlaying(!currentStatus);

    if(this->manager->isPlaying())
    {
        this->manager->playVideo();
    }

    std::cout << "Button PLAY Pressed: " << this->manager->getFrameId() << std::endl;
}

void MainWindow::slot_slideVideo(int _frameId)
{
    double dFrame = static_cast<double>(_frameId);

    Mat frameMat = this->manager->getFrame(dFrame);
    if(frameMat.data)
    {
        QImage frameQImage = this->manager->matToQimage(frameMat);

        this->ui->labelFrameShow->setPixmap(QPixmap::fromImage(frameQImage));
        this->ui->labelFrameId->setText(QString::number(_frameId) + "/" + QString::number(this->totalFrames));
    }
}
