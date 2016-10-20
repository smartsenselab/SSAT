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
    this->setTable();
}

MainWindow::~MainWindow()
{
    delete(this->manager);
    delete(this->playerTime);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    this->ui->viewFrame->fitInView(this->frameScene.sceneRect(), Qt::KeepAspectRatio);
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
    this->ui->actionAttributes->setEnabled(_enable);

    this->ui->buttonForward->setEnabled(_enable);
    this->ui->buttonForwardF->setEnabled(_enable);
    this->ui->buttonPlay->setEnabled(_enable);
    this->ui->buttonRewind->setEnabled(_enable);
    this->ui->buttonRewindF->setEnabled(_enable);
    this->ui->buttonStop->setEnabled(_enable);

    this->ui->labelFrameId->setEnabled(_enable);
    this->ui->labelTime->setEnabled(_enable);
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

    // Connecting ACTIONS to SLOTS
    this->connect(this->ui->actionOpen,
                  &QAction::triggered,
                  this,
                  &MainWindow::slot_openFile
                  );

    this->connect(this->ui->actionAttributes,
                  &QAction::triggered,
                  this,
                  &MainWindow::slot_openAttributes
                  );

    // Connecting SIGNALS to SLOTS
    this->connect(this->ui->sliderFrame,
                  SIGNAL(sliderMoved(int)),
                  this,
                  SLOT(slot_slideVideo(int))
                  );

    this->connect(this->ui->buttonPlay,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_playButtonPressed())
                  );

    this->connect(this->ui->buttonRewindF,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_rewindButtonPressed())
                  );

    this->connect(this->ui->buttonRewind,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_backButtonPressed())
                  );

    this->connect(this->ui->buttonForward,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_forwardButtonPressed())
                  );

    this->connect(this->ui->buttonForwardF,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_fastfButtonPressed())
                  );

    this->connect(this->ui->buttonStop,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_stopButtonPressed())
                  );

    this->connect(this->ui->spinBoxSpeed,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_spinBoxSpeedValueChanged(int))
                  );

    // Connecting custom SIGNALS to SLOTS
    this->connect(&(this->frameScene),
                  SIGNAL(signal_addBoundingBoxToCore(Rect)),
                  this,
                  SLOT(slot_addBoundingBoxToCore(Rect))
                  );

    this->connect(this,
                  SIGNAL(signal_drawFrameBboxes(const Frame)),
                  &(this->frameScene),
                  SLOT(slot_drawFrameBboxes(const Frame))
                  );
}

void MainWindow::setTable()
{
    QStringList headerLabels;
    QHeaderView* header = ui->tableWidget->horizontalHeader();

    headerLabels << "Tracker" << "Ini" << "End" << "Cancel";
    header->setSectionResizeMode(QHeaderView::Stretch);

    this->ui->tableWidget->setColumnCount(4);
    this->ui->tableWidget->setHorizontalHeaderLabels(headerLabels);
}

void MainWindow::changeSpeed(const int _speed)
{
    this->speed = (_speed - 1) * 5;
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

void MainWindow::updateFrame()
{
    Mat frameMat = this->manager->getFrame();
    unsigned long nextFrameId = static_cast<unsigned long>(this->manager->getFrameId());

    if(frameMat.data)
    {
        int currentFrame = this->ui->sliderFrame->value() + 1;
        this->ui->sliderFrame->setValue(static_cast<int>(currentFrame));
        this->ui->labelFrameId->setText(QString::number(currentFrame) + "/" + QString::number(this->totalFrames));

        this->frameScene.clear();

        qint64 current = this->manager->getTime();
        QTime currentTime((current/3600)%60, (current/60)%60, current%60, (current*1000)%1000);
        QString stringTime = currentTime.toString("hh:mm:ss");
        this->ui->labelTime->setText(stringTime);

        this->frameQImage = this->manager->matToQimage(frameMat);
        this->frameScene.addPixmap(QPixmap::fromImage(frameQImage));

        this->ui->viewFrame->setScene(&(this->frameScene));
        this->ui->viewFrame->fitInView(this->frameScene.sceneRect(), Qt::KeepAspectRatio);

        emit signal_drawFrameBboxes(this->singleton->frames[nextFrameId - 1]);
    }
}

void MainWindow::updateFrame(const int _frameId)
{
    Mat frameMat = this->manager->getFrame(_frameId + this->speed);
    unsigned long nextFrameId = static_cast<unsigned long>(this->manager->getFrameId());

    if(frameMat.data)
    {
        this->ui->sliderFrame->setValue(static_cast<int>(_frameId));
        this->ui->labelFrameId->setText(QString::number(_frameId) + "/" + QString::number(this->totalFrames));

        this->frameScene.clear();

        qint64 current = this->manager->getTime();
        QTime currentTime((current/3600)%60, (current/60)%60, current%60, (current*1000)%1000);
        QString stringTime = currentTime.toString("hh:mm:ss");
        this->ui->labelTime->setText(stringTime);

        this->frameQImage = this->manager->matToQimage(frameMat);
        this->frameScene.addPixmap(QPixmap::fromImage(frameQImage));

        this->ui->viewFrame->setScene(&(this->frameScene));
        this->ui->viewFrame->fitInView(this->frameScene.sceneRect(), Qt::KeepAspectRatio);

        emit signal_drawFrameBboxes(this->singleton->frames[static_cast<unsigned long>(nextFrameId - 1)]);
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
        this->totalFrames = std::round(+this->manager->getTotalFrames());

        if(this->singleton == NULL)
        {
            this->singleton = Core::getInstance(static_cast<unsigned int>(this->totalFrames));
        }
        else
        {
            this->singleton->reset(static_cast<unsigned int>(this->totalFrames));
        }

        this->ui->sliderFrame->setEnabled(true);
        this->ui->sliderFrame->setRange(1, static_cast<int>(this->totalFrames));

        this->enableWidgets(true);
        this->updateFrame(1);
    }
}

void MainWindow::slot_openAttributes()
{
    this->singleton->attributes.insert(std::pair<string, string>("Object_recognition", "Table"));
    this->singleton->attributes.insert(std::pair<string, string>("Object_recognition", "Tennis"));
    this->singleton->attributes.insert(std::pair<string, string>("Object_recognition", "Desk"));
    this->singleton->attributes.insert(std::pair<string, string>("Object_recognition", "Television"));

    this->singleton->attributes.insert(std::pair<string, string>("Person_identification", "Breno"));
    this->singleton->attributes.insert(std::pair<string, string>("Person_identification", "Danilo"));
    this->singleton->attributes.insert(std::pair<string, string>("Person_identification", "Davi"));
    this->singleton->attributes.insert(std::pair<string, string>("Person_identification", "Rafael"));

    this->annotationDialog = new DialogAnnotation(this);
    this->annotationDialog->slot_initializeDialog(*(this->singleton));
    this->annotationDialog->setModal(true);
    this->annotationDialog->show();
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
    contextMenu.addAction("New Bounding box", this, SLOT(slot_newBoxMenu()));
    contextMenu.addAction("New Frame box", this, SLOT(slot_newFrameMenu()));
    contextMenu.addAction("Remove Bbox", this, SLOT(slot_removeBoxMenu()));

    contextMenu.exec(position);
}

void MainWindow::slot_playButtonPressed()
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

void MainWindow::slot_rewindButtonPressed()
{
    int nextFrameId = static_cast<int>(this->manager->getFrameId());
    this->slot_rewindButtonPressed(nextFrameId);
}

void MainWindow::slot_rewindButtonPressed(const int _frameId)
{
    int nextFrameId = static_cast<int>(_frameId - std::round(+this->manager->getTotalFrames() / 100.0));
    if(nextFrameId < 1)
    {
        nextFrameId = 1;
    }

    this->updateFrame(nextFrameId);
}

void MainWindow::slot_backButtonPressed()
{
    int nextFrameId = static_cast<int>(this->manager->getFrameId());
    this->slot_backButtonPressed(nextFrameId);
}

void MainWindow::slot_backButtonPressed(const int _frameId)
{
    int nextFrameId = _frameId - 2;
    if(nextFrameId < 1)
    {
        nextFrameId = 1;
    }

    this->updateFrame(nextFrameId);
}

void MainWindow::slot_forwardButtonPressed()
{
    int nextFrameId = static_cast<int>(this->manager->getFrameId());
    this->slot_forwardButtonPressed(nextFrameId);
}

void MainWindow::slot_forwardButtonPressed(const int _frameId)
{
    int nextFrameId = _frameId;
    if(nextFrameId > (this->manager->getTotalFrames()))
    {
        nextFrameId = static_cast<int>(this->manager->getTotalFrames());
    }

    this->updateFrame(nextFrameId);
}

void MainWindow::slot_fastfButtonPressed()
{
    int nextFrameId = static_cast<int>(this->manager->getFrameId());
    this->slot_fastfButtonPressed(nextFrameId);
}

void MainWindow::slot_fastfButtonPressed(const int _frameId)
{
    int nextFrameId = static_cast<int>(_frameId + std::round(+this->manager->getTotalFrames() / 100.0));
    if(nextFrameId > this->manager->getTotalFrames())
    {
        nextFrameId = static_cast<int>(this->manager->getTotalFrames());
    }

    this->updateFrame(nextFrameId);
}

void MainWindow::slot_stopButtonPressed()
{
    this->isPlaying(false);
    this->stopVideo();
}

void MainWindow::slot_spinBoxSpeedValueChanged(int _value)
{
    this->changeSpeed(_value);
}

void MainWindow::slot_keepVideoRunning()
{
    int nextFrameId = static_cast<int>(this->manager->getFrameId());

    if(nextFrameId == static_cast<int>(this->totalFrames))
    {
        this->slot_stopButtonPressed();
    }
    else
    {
        if(this->speed == 0)
        {
            this->updateFrame();
        }
        else
        {
            this->updateFrame(nextFrameId);
        }
    }
}

void MainWindow::slot_newBoxMenu()
{
    this->frameScene.slot_enableDraw();

    // CheckBox
    QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
    checkBoxItem->setCheckState(Qt::Unchecked);

    // Cancel Button
    QPushButton* btn_cancel = new QPushButton();
    btn_cancel = new QPushButton();
    btn_cancel->setText("Cancel");
    //btn_cancel->setIcon(QIcon("https://t4.ftcdn.net/jpg/00/08/30/29/500_F_8302961_GVoPsXWcNsfvVygwE2sri9m9aISpJgYQ.jpg"));

    // Table row
    int row = this->ui->tableWidget->rowCount() - 1;
    this->ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    this->ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, checkBoxItem);
    this->ui->tableWidget->setCellWidget(row, 3, btn_cancel);
}

void MainWindow::slot_newFrameMenu()
{
    this->frameDialog = new DialogFrameBased(this);

    this->connect(this->frameDialog,
                  SIGNAL(signal_rewindButtonPressed()),
                  this,
                  SLOT(slot_rewindButtonPressed())
                  );

    this->connect(this->frameDialog,
                  SIGNAL(signal_backButtonPressed()),
                  this,
                  SLOT(slot_backButtonPressed())
                  );

    this->connect(this->frameDialog,
                  SIGNAL(signal_forwardButtonPressed()),
                  this,
                  SLOT(slot_forwardButtonPressed())
                  );

    this->connect(this->frameDialog,
                  SIGNAL(signal_fastfButtonPressed()),
                  this,
                  SLOT(slot_fastfButtonPressed())
                  );

    this->connect(this->frameDialog,
                  SIGNAL(signal_frameBasedOkButtonPressed(const FrameBasedData)),
                  this,
                  SLOT(slot_frameBasedOkButtonPressed(const FrameBasedData))
                  );

    this->frameDialog->setModal(true);
    this->frameDialog->show();

    int nextFrameId = static_cast<int>(this->manager->getFrameId());
    int totalFrames = static_cast<int>(this->manager->getTotalFrames());

    this->frameDialog->slot_initializeDialog(totalFrames, nextFrameId);
}

void MainWindow::slot_removeBoxMenu()
{

}

void MainWindow::slot_frameBasedOkButtonPressed(const FrameBasedData _data)
{
    this->manager->allotFrameBasedSegment(*(this->singleton), _data);
}

void MainWindow::slot_addBoundingBoxToCore(const Rect _box)
{
    unsigned long nextFrameId = static_cast<unsigned long>(this->manager->getFrameId());
    unsigned long num_bboxes = this->singleton->frames[nextFrameId - 1].getBoxes().size();

    string temp_id = "frame" + std::to_string(nextFrameId - 1);
    string temp_key = "bbox" + std::to_string(num_bboxes);

    this->singleton->frames[nextFrameId - 1].addBox(temp_id + "_" + temp_key, _box);
}
