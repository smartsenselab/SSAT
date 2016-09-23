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
    this->speed = 0;

    this->enableWidgets(false);
    this->connectSignalSlots();
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
    this->ui->spinBoxSpeed->setEnabled(_enable);
    this->ui->viewFrame->setEnabled(_enable);
}

void MainWindow::connectSignalSlots()
{
    // Adding context menu to labelFrameShow
    this->ui->viewFrame->setContextMenuPolicy(Qt::CustomContextMenu);
    this->connect(this->ui->viewFrame,
                  SIGNAL(customContextMenuRequested(QPoint)),
                  this,
                  SLOT(slot_contextMenu(QPoint))
                  );

    // Connecting SIGNALS to SLOTS
    this->connect(ui->actionOpen,
                  &QAction::triggered,
                  this,
                  &MainWindow::slot_openFile
                  );

    this->connect(this->ui->sliderFrame,
                  SIGNAL(sliderMoved(int)),
                  this,
                  SLOT(slot_slideVideo(int))
                  );

    this->connect(this->ui->buttonPlay,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_playButton())
                  );

    this->connect(this->ui->buttonRewindF,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_rewindButton())
                  );

    this->connect(this->ui->buttonRewind,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_backButton())
                  );

    this->connect(this->ui->buttonForward,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_forwardButton())
                  );

    this->connect(this->ui->buttonForwardF,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_fastfButton())
                  );

    this->connect(this->ui->buttonStop,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_stopButton())
                  );

    this->connect(this->ui->spinBoxSpeed,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_spinBoxSpeed(int))
                  );
}

void MainWindow::changeSpeed(const int _speed)
{
    if (this->playerTime != NULL)
    {
        this->speed = _speed - 1;
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
    int interval = static_cast<int>(frameRate);

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
    Mat frameMat = this->manager->getFrame(_frameId + this->speed);
    if(frameMat.data)
    {
        this->ui->sliderFrame->setValue(static_cast<int>(_frameId));
        this->ui->labelFrameId->setText(QString::number(_frameId) + "/" + QString::number(this->totalFrames));

        QImage frameQImage = this->manager->matToQimage(frameMat);

        this->frameScene.addPixmap(QPixmap::fromImage(frameQImage));
        this->ui->viewFrame->setScene(&(this->frameScene));
    }
}

void MainWindow::slot_displayFrame(const QImage _frame)
{
    if(!_frame.isNull())
    {
        this->frameScene.addPixmap(QPixmap::fromImage(_frame));
        this->ui->viewFrame->setScene(&(this->frameScene));
    }
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

void MainWindow::slot_contextMenu(const QPoint &_point)
{
    QPoint position = this->ui->viewFrame->mapToGlobal(_point);

    QMenu contextMenu;
    contextMenu.addAction("New Bbox", this, SLOT(slot_newBox()));
    contextMenu.addAction("Adjust Bbox");
    contextMenu.addAction("Remove Bbox");

    contextMenu.exec(position);
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

void MainWindow::slot_newBox()
{
    QPen bluePen(Qt::blue);
    this->rectangle = this->frameScene.addRect(10,
                                               10,
                                               100,
                                               100,
                                               bluePen
                                               );
}
