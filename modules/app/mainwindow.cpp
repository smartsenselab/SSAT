#include <iostream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    this->loaded = false;
    this->manager = new VideoManager;
    this->playing = false;

    this->enableWidgets(false);

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
                  SLOT(slot_playButton())
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

    this->connect(ui->buttonStop,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_stopButton())
                  );

    this->connect(ui->spinBoxSpeed,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_spinBoxSpeed(int))
                  );
}

MainWindow::~MainWindow()
{
    delete(this->manager);
    delete(this->playerTime);
}

bool MainWindow::isPlaying()
{
    return this->playing;
}

void MainWindow::isPlaying(const bool _enable)
{
    this->playing = _enable;
    if(_enable)
    {
        this->ui->buttonPlay->setText("Pause");
    }
    else
    {
        this->ui->buttonPlay->setText("Play");
    }
}

void MainWindow::enableWidgets(const bool _enable)
{
    this->ui->buttonForward->setEnabled(_enable);
    this->ui->buttonForwardF->setEnabled(_enable);
    this->ui->buttonPlay->setEnabled(_enable);
    this->ui->buttonRewind->setEnabled(_enable);
    this->ui->buttonRewindF->setEnabled(_enable);
    this->ui->buttonStop->setEnabled(_enable);

    this->ui->labelFrameId->setEnabled(_enable);
    this->ui->sliderFrame->setEnabled(_enable);
}

void MainWindow::changeSpeed(const int _speed)
{
    if (this->playerTime != NULL)
    {
        double frameRate = this->manager->getVideoFPS();
        int interval = static_cast<int>(1000/(_speed * frameRate));

        this->playerTime->stop();
        this->playerTime->setInterval(interval);
        this->playerTime->start();
    }
}

void MainWindow::pauseVideo()
{
    if (this->playerTime != NULL)
    {
        this->playerTime->stop();

        delete(this->playerTime);
        this->playerTime = NULL;
    }
}

void MainWindow::playVideo()
{
    if (this->playerTime == NULL)
    {
        this->playerTime = new QTimer;
    }

    double frameRate = this->manager->getVideoFPS();
    int speed = this->ui->spinBoxSpeed->value();
    int interval = static_cast<int>(1000/(speed * frameRate));

    this->playerTime->setInterval(interval);
    this->playerTime->setSingleShot(false);

    connect(this->playerTime,
            SIGNAL(timeout()),
            this,
            SLOT(slot_keepVideoRunning())
            );

    this->playerTime->start();
}

void MainWindow::stopVideo()
{
    this->updateFrame(1);

    if (this->playerTime != NULL)
    {
        this->playerTime->stop();

        delete(this->playerTime);
        this->playerTime = NULL;
    }
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

    if(!videoName.isEmpty())
    {
        this->manager->loadVideo(videoName);

        this->loaded = true;
        this->totalFrames = std::round(+this->manager->getTotalFrames() - 2);

        this->ui->sliderFrame->setEnabled(true);
        this->ui->sliderFrame->setRange(1, static_cast<int>(this->totalFrames));

        this->enableWidgets(true);
        this->updateFrame(1);
    }
}

void MainWindow::slot_slideVideo(int _frameId)
{
    std::cout << _frameId << std::endl;
    this->updateFrame(_frameId);
}

void MainWindow::slot_playButton()
{
    if(!this->playing)
    {
        this->isPlaying(true);
        this->playVideo();
    }
    else
    {
        this->isPlaying(false);
        this->pauseVideo();
    }

}

void MainWindow::slot_rewindButton()
{
    int frameId = static_cast<int>(this->manager->getFrameId());
    frameId -= std::round(+this->manager->getTotalFrames() / 100.0);

    if(frameId < 1)
    {
        frameId = 1;
    }

    this->updateFrame(frameId);
}

void MainWindow::slot_backButton()
{
    int frameId = static_cast<int>(this->manager->getFrameId());
    frameId--;

    if(frameId < 1)
    {
        frameId = 1;
    }

    this->updateFrame(frameId);
}

void MainWindow::slot_forwardButton()
{
    int frameId = static_cast<int>(this->manager->getFrameId());
    frameId++;

    if(frameId > (this->manager->getTotalFrames() - 1))
    {
        frameId = static_cast<int>(this->manager->getTotalFrames() - 1);
    }

    this->updateFrame(frameId);
}

void MainWindow::slot_fastfButton()
{
    int frameId = static_cast<int>(this->manager->getFrameId());
    frameId += std::round(+this->manager->getTotalFrames() / 100.0);

    if(frameId > this->manager->getTotalFrames() - 1)
    {
        frameId = static_cast<int>(this->manager->getTotalFrames() - 1);
    }

    this->updateFrame(frameId);
}

void MainWindow::slot_stopButton()
{
    this->isPlaying(false);
    this->stopVideo();
}

void MainWindow::slot_spinBoxSpeed(int _value)
{
    this->changeSpeed(_value);
}

void MainWindow::slot_keepVideoRunning()
{
    int frameId = static_cast<int>(this->manager->getFrameId());

    if(frameId == static_cast<int>(this->totalFrames))
    {
        this->slot_stopButton();
    }
    else
    {
        this->updateFrame(frameId);
    }
}
