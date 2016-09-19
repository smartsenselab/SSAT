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

    this->connect(ui->buttonRewindF,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_rewindButton())
                  );

    this->connect(ui->buttonRewind,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_backButton())
                  );

    this->connect(ui->buttonForward,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_forwardButton())
                  );

    this->connect(ui->buttonForwardF,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_fastfButton())
                  );
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateFrame(const int _frameId)
{
    Mat frameMat = this->manager->getFrame(_frameId);
    if(frameMat.data)
    {
        QImage frameQImage = this->manager->matToQimage(frameMat);
        this->ui->sliderFrame->setValue(static_cast<int>(_frameId));
        this->ui->labelFrameId->setText(QString::number(_frameId) + "/" + QString::number(this->totalFrames));
        this->ui->labelFrameShow->setPixmap(QPixmap::fromImage(frameQImage));
    }
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
    this->totalFrames = std::round(+this->manager->getTotalFrames() - 2);

    this->ui->sliderFrame->setEnabled(true);
    this->ui->sliderFrame->setRange(1, static_cast<int>(this->totalFrames));

    this->updateFrame(1);
}

void MainWindow::slot_slideVideo(int _frameId)
{
    std::cout << _frameId << std::endl;
    this->updateFrame(_frameId);
}

void MainWindow::slot_playButton()
{
    bool currentStatus = this->manager->isPlaying();
    this->manager->isPlaying(!currentStatus);

    if(this->manager->isPlaying())
    {
        this->manager->playVideo();
    }

    std::cout << "Button PLAY Pressed: " << this->manager->getFrameId() << std::endl;
}

void MainWindow::slot_rewindButton()
{
    int frameId = this->manager->getFrameId();
    frameId -= std::round(+this->manager->getTotalFrames() / 100.0);

    if(frameId < 1)
    {
        frameId = 1;
    }

    this->updateFrame(frameId);
}

void MainWindow::slot_backButton()
{
    int frameId = this->manager->getFrameId();
    frameId--;

    if(frameId < 1)
    {
        frameId = 1;
    }

    this->updateFrame(frameId);
}

void MainWindow::slot_forwardButton()
{
    int frameId = this->manager->getFrameId();
    frameId++;

    if(frameId > this->manager->getTotalFrames() - 1)
    {
        frameId = this->manager->getTotalFrames() - 1;
    }

    this->updateFrame(frameId);
}

void MainWindow::slot_fastfButton()
{
    int frameId = this->manager->getFrameId();
    frameId += std::round(+this->manager->getTotalFrames() / 100.0);

    if(frameId > this->manager->getTotalFrames() - 1)
    {
        frameId = this->manager->getTotalFrames() - 1;
    }

    this->updateFrame(frameId);
}

void MainWindow::slot_stopButton()
{

}
