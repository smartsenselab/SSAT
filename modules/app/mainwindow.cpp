#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);

    this->frameScene = new QBoundingBoxScene(this);
    this->loaded = false;
    this->manager = new VideoManager;
    this->playing = false;
    this->saveTimer = new QTimer(this);
    this->speed = 0;

    this->enableWidgets(false);
    this->enableFrameBased(false);
    this->connectSignalSlots();
    this->setShortcuts();
    this->setTableModel();

    this->ui->splitterHorizontal->setStretchFactor(0,1);
    this->ui->splitterVertical->setStretchFactor(0,1);

    this->ui->viewFrame->setWindowFlags(Qt::SubWindow);
}

MainWindow::~MainWindow()
{
    delete(this->manager);
    delete(this->playerTime);
}

void MainWindow ::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Delete:
        this->slot_tableViewRemoveAnnotation();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    this->ui->viewFrame->fitInView(this->frameScene->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::enableWidgets(const bool _enable)
{
    this->ui->actionAttributes->setEnabled(_enable);
    this->ui->actionExport_JSON->setEnabled(_enable);
    this->ui->actionImport_JSON->setEnabled(_enable);

    this->ui->buttonForward->setEnabled(_enable);
    this->ui->buttonForwardF->setEnabled(_enable);
    this->ui->buttonPlay->setEnabled(_enable);
    this->ui->buttonRewind->setEnabled(_enable);
    this->ui->buttonRewindF->setEnabled(_enable);
    this->ui->buttonStop->setEnabled(_enable);
    this->ui->buttonNewBox->setEnabled(_enable);

    this->ui->labelFrameId->setEnabled(_enable);
    this->ui->labelTime->setEnabled(_enable);
    this->ui->sliderFrame->setEnabled(_enable);
    this->ui->spinBoxSpeed->setEnabled(_enable);
    this->ui->tableViewFrame->setEnabled(_enable);
    this->ui->viewFrame->setEnabled(_enable);
    this->ui->labelSpeed->setEnabled(_enable);
    this->ui->buttonTool->setEnabled(_enable);
}

void MainWindow::enableFrameBased(const bool _enable)
{
    this->frameBasedIsEnable = _enable;
    this->ui->comboBoxCategory->clear();
    this->ui->comboBoxLabel->clear();
    if(_enable == false)
    {
        this->ui->spinBoxFinalFrame->clear();
        this->ui->spinBoxInitialFrame->clear();
    }
    else
    {
        this->ui->spinBoxInitialFrame->setValue(this->ui->sliderFrame->value());
        this->ui->spinBoxFinalFrame->setValue(this->ui->sliderFrame->value());
    }
    this->ui->lineEditInfo->clear();

    this->ui->comboBoxCategory->setEnabled(_enable);
    this->ui->comboBoxLabel->setEnabled(_enable);
    this->ui->spinBoxFinalFrame->setEnabled(_enable);
    this->ui->spinBoxInitialFrame->setEnabled(_enable);
    this->ui->lineEditInfo->setEnabled(_enable);
    this->ui->buttonBoxOKcancel->setEnabled(_enable);
    this->ui->labelCategory->setEnabled(_enable);
    this->ui->labelLabel->setEnabled(_enable);
    this->ui->labelInitialFrame->setEnabled(_enable);
    this->ui->labelFinalFrame->setEnabled(_enable);
    this->ui->labelInfo->setEnabled(_enable);
}

void MainWindow::connectSignalSlots()
{
    // Adding context menu to viewFrame
    this->ui->viewFrame->setContextMenuPolicy(Qt::CustomContextMenu);
    this->connect(this->ui->viewFrame,
                  SIGNAL(customContextMenuRequested(QPoint)),
                  this,
                  SLOT(slot_viewFrameContextMenu(QPoint))
                  );

    // Adding context menu to tableViewFrame
    this->ui->tableViewFrame->setContextMenuPolicy(Qt::CustomContextMenu);
    this->connect(this->ui->tableViewFrame,
                  SIGNAL(customContextMenuRequested(QPoint)),
                  this,
                  SLOT(slot_tableViewContextMenu(QPoint))
                  );

    // Connecting ACTIONS to SLOTS
    this->connect(this->ui->actionOpen,
                  &QAction::triggered,
                  this,
                  &MainWindow::slot_openFile
                  );
    this->connect(this->ui->actionImport_JSON,
                  &QAction::triggered,
                  this,
                  &MainWindow::slot_importJson
                  );

    this->connect(this->ui->actionExport_JSON,
                  &QAction::triggered,
                  this,
                  &MainWindow::slot_exportJson
                  );

    this->connect(this->ui->actionExit,
                  &QAction::triggered,
                  this,
                  &MainWindow::slot_closeApplitacion
                  );

    this->connect(this->ui->actionAttributes,
                  &QAction::triggered,
                  this,
                  &MainWindow::slot_openAttributesDialog
                  );

    // Connecting PLAYER SIGNALS to SLOTS
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

    this->connect(this->ui->buttonNewBox,
                  SIGNAL(pressed()),
                  this,
                  SLOT(slot_viewFrameNewBoxMenu())
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

    // Connecting TABLE_VIEW_FRAME SIGNALS to SLOTS
    this->connect(this->ui->tableViewFrame,
                  SIGNAL(clicked(QModelIndex)),
                  this,
                  SLOT(slot_tableviewFrameSingleClicked(QModelIndex))
                  );

    this->connect(this->ui->tableViewFrame,
                  SIGNAL(doubleClicked(QModelIndex)),
                  this,
                  SLOT(slot_tableViewFrameDoubleClicked(QModelIndex))
                  );

    this->connect(this->ui->tableViewFrame->horizontalHeader(),
                  SIGNAL(sectionClicked(int)),
                  this,
                  SLOT(slot_on_sectionClicked(int))
                  );

    // Connecting INFO PANEL SIGNALS to SLOTS
    this->connect(this->ui->comboBoxCategory,
                  SIGNAL(activated(QString)),
                  this,
                  SLOT(slot_comboBoxCategoryActivated(QString))
                  );

    this->connect(this->ui->spinBoxInitialFrame,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_spinBoxValueChanged())
                  );

    this->connect(this->ui->spinBoxFinalFrame,
                  SIGNAL(valueChanged(int)),
                  this,
                  SLOT(slot_spinBoxValueChanged())
                  );

    this->connect(this->ui->buttonBoxOKcancel,
                  SIGNAL(accepted()),
                  this,
                  SLOT(slot_buttonBoxAccepted())
                  );

    this->connect(this->ui->buttonBoxOKcancel,
                  SIGNAL(rejected()),
                  this,
                  SLOT(slot_buttonBoxRejected())
                  );

    this->connect(this->ui->splitterHorizontal,
                  SIGNAL(splitterMoved(int, int)),
                  this,
                  SLOT(slot_resizeFrame())
                  );

    this->connect(this->saveTimer,
                  SIGNAL(timeout()),
                  SLOT(slot_backupJson())
                  );

    // Connecting custom frame-based SIGNALS to SLOTS
    this->connect(this,
                  SIGNAL(signal_frameBasedInsertAccepted(FrameBasedData)),
                  this,
                  SLOT(slot_frameBasedInsertAccepted(const FrameBasedData))
                  );

    this->connect(this,
                  SIGNAL(signal_frameBasedAlterAccepted(const FrameBasedData, const int)),
                  this,
                  SLOT(slot_frameBasedAlterAccepted(const FrameBasedData, const int))
                  );

    // Connecting custom boundingbox-based SIGNALS to SLOTS
    this->connect(this->frameScene,
                  SIGNAL(signal_openBoundingBoxDialog(const unsigned int)),
                  this,
                  SLOT(slot_openBoundingBoxDialog(const unsigned int))
                  );

    this->connect(this->frameScene,
                  SIGNAL(signal_addBoundingBoxToCore(const Rect)),
                  this,
                  SLOT(slot_addBoundingBoxToCore(const Rect))
                  );

    this->connect(this->frameScene,
                  SIGNAL(signal_moveBoundingBoxInCore(const unsigned int, const Rect)),
                  this,
                  SLOT(slot_moveBoundingBoxInCore(const unsigned int, const Rect))
                  );

    this->connect(this->frameScene,
                  SIGNAL(signal_removeBoundingBoxFromCore(const unsigned int)),
                  this,
                  SLOT(slot_removeBoundingBoxFromCore(const unsigned int))
                  );

    this->connect(this,
                  SIGNAL(signal_drawFrameBboxes(const Frame)),
                  this->frameScene,
                  SLOT(slot_drawFrameBboxes(const Frame))
                  );
}

void MainWindow::setShortcuts()
{
    this->crtb = new QAction(tr("id1"), this);
    this->crtb->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_B);
    this->addAction(crtb);

    this->crtf = new QAction(tr("id2"), this);
    this->crtf->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_F);
    this->addAction(crtf);

    // Connecting SHORTCUTS to SLOTS
    this->connect(this->crtb, SIGNAL(triggered()), SLOT(slot_Bshortcut()));
    this->connect(this->crtf, SIGNAL(triggered()), SLOT(slot_Fshortcut()));
}

void MainWindow::setTableModel()
{
    this->tableModel = new QFrameBasedTableModel(this);
    this->ui->tableViewFrame->setAlternatingRowColors(true);
    this->ui->tableViewFrame->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->tableViewFrame->setSelectionBehavior(QAbstractItemView::SelectRows);

    this->connect(this,
                  SIGNAL(signal_sortTable(int)),
                  this->tableModel,
                  SLOT(slot_sortTable(int))
                  );
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
    cv::Mat frameMat = this->manager->getFrame();
    unsigned long nextFrameId = static_cast<unsigned long>(this->manager->getFrameId());

    if(frameMat.data)
    {
        int currentFrame = this->ui->sliderFrame->value() + 1;
        this->ui->sliderFrame->setValue(static_cast<int>(currentFrame));
        this->ui->labelFrameId->setText(QString::number(currentFrame) + "/" + QString::number(this->totalFrames));

        this->frameScene->clear();

        qint64 current = this->manager->getTime();
        QTime currentTime((current/3600)%60, (current/60)%60, current%60, (current*1000)%1000);
        QString stringTime = currentTime.toString("hh:mm:ss");
        this->ui->labelTime->setText(stringTime);

        this->frameQImage = this->manager->matToQimage(frameMat);
        this->frameScene->addPixmap(QPixmap::fromImage(frameQImage));

        this->ui->viewFrame->setScene((this->frameScene));
        this->ui->viewFrame->fitInView(this->frameScene->sceneRect(), Qt::KeepAspectRatio);

        emit signal_drawFrameBboxes(this->singleton->frames[nextFrameId - 1]);
    }
}

void MainWindow::updateFrame(const int _frameId)
{
    cv::Mat frameMat = this->manager->getFrame(_frameId + this->speed);
    unsigned long nextFrameId = static_cast<unsigned long>(this->manager->getFrameId());

    if(frameMat.data)
    {
        this->ui->sliderFrame->setValue(static_cast<int>(_frameId));
        this->ui->labelFrameId->setText(QString::number(_frameId) + "/" + QString::number(this->totalFrames));

        this->frameScene->clear();

        qint64 current = this->manager->getTime();
        QTime currentTime((current/3600) % 60, (current/60) % 60, current % 60, (current * 1000) % 1000);
        QString stringTime = currentTime.toString("hh:mm:ss");
        this->ui->labelTime->setText(stringTime);

        this->frameQImage = this->manager->matToQimage(frameMat);
        this->frameScene->addPixmap(QPixmap::fromImage(frameQImage));
        this->frameScene->updateSceneSize();

        this->ui->viewFrame->setScene((this->frameScene));
        this->ui->viewFrame->fitInView(this->frameScene->sceneRect(), Qt::KeepAspectRatio);

        emit signal_drawFrameBboxes(this->singleton->frames[static_cast<unsigned long>(nextFrameId - 1)]);
    }
}

void MainWindow::messageRestoreJson()
{
    std::ifstream file(this->corePath.toStdString());
    if (file.good())
    {
        QMessageBox message;
        message.setIcon(QMessageBox::Warning);
        message.setText("There is a backup file in your directory.");
        message.setInformativeText("Do you want to restore previous settings");
        message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        int response = message.exec();

        switch(response)
        {
        case QMessageBox::Yes:
            this->manager->importJSON(*(this->singleton), this->tableModel, this->corePath);
        }
    }
}

int MainWindow::getIniFrameValue()
{
    return this->ui->spinBoxInitialFrame->value();
}

int MainWindow::getEndFrameValue()
{
    return this->ui->spinBoxFinalFrame->value();
}

QString MainWindow::getInfoValue()
{
    return this->ui->lineEditInfo->text();
}

void MainWindow::initializeComboboxes()
{
    QStringList categoryList, labelList;
    QSet<QString> categorySet, labelSet;

    // populate comboBoxCategory
    multimap<string, string>::iterator it;
    for(it = this->singleton->attributes.begin(); it != this->singleton->attributes.end(); it++)
    {
        categorySet.insert(QString::fromStdString(it->first));
    }
    categoryList.append(categorySet.toList());

    this->categoryModel = new QStringListModel(this);
    this->categoryModel->setStringList(categoryList);
    this->ui->comboBoxCategory->setModel(this->categoryModel);

    // populate comboBoxLabel
    string category = this->ui->comboBoxCategory->currentText().toStdString();
    for(it = this->singleton->attributes.lower_bound(category); it != this->singleton->attributes.upper_bound(category); it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel = new QStringListModel(this);
    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);
}

void MainWindow::initializeComboboxes(QString const _category)
{
    QStringList categoryList, labelList;
    QSet<QString> categorySet, labelSet;
    string category = _category.toStdString();

    // populate comboBoxCategory
    multimap<string, string>::iterator it;
    for(it = this->singleton->attributes.begin(); it != this->singleton->attributes.end(); it++)
    {
        categorySet.insert(QString::fromStdString(it->first));
    }
    categoryList.append(categorySet.toList());

    this->categoryModel = new QStringListModel(this);
    this->categoryModel->setStringList(categoryList);
    this->ui->comboBoxCategory->setModel(this->categoryModel);

    // populate comboBoxLabel
    for(it = this->singleton->attributes.lower_bound(category); it != this->singleton->attributes.upper_bound(category); it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel = new QStringListModel(this);
    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);
}

void MainWindow::enableDisableButtonBox()
{
    int iniIndex = this->ui->spinBoxInitialFrame->value();
    int endIndex = this->ui->spinBoxFinalFrame->value();

    if(endIndex < iniIndex)
    {
        this->ui->buttonBoxOKcancel->setEnabled(false);
    }
    else
    {
        this->ui->buttonBoxOKcancel->setEnabled(true);
    }
}

void MainWindow::slot_Fshortcut()
{
    if(!this->isPlaying())
    {
        this->slot_viewFrameNewFrameMenu();
        this->enableFrameBased(true);
    }
}

void MainWindow::slot_Ashortcut()
{
    this->slot_openAttributesDialog();
}

void MainWindow::slot_Oshortcut()
{
    this->slot_openFile();
}

void MainWindow::slot_Wshortcut()
{
    this->slot_closeApplitacion();
}

void MainWindow::slot_Ishortcut()
{
    slot_importJson();
}

void MainWindow::slot_Eshortcut()
{
    this->slot_exportJson();
}

void MainWindow::slot_Bshortcut()
{
    this->slot_viewFrameNewBoxMenu();
}

void MainWindow::slot_displayFrame(const QImage _frame)
{
    if(!_frame.isNull())
    {
        this->frameScene->addPixmap(QPixmap::fromImage(_frame));
        this->ui->viewFrame->setScene((this->frameScene));
    }
}

void MainWindow::slot_openFile()
{
    QString videoName = QFileDialog::getOpenFileName(this,
                                                     tr("Open Video..."),
                                                     tr(QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString().c_str()),
                                                     tr("Video Files (*.avi *.mp4 *.mov)"));

    if(!videoName.isEmpty())
    {
        delete this->frameScene;
        this->tableModel->clear();

        // Re-instantiating frameScene and its Signal/Slot connections
        this->frameScene = new QBoundingBoxScene(this);

        this->connect(this->frameScene,
                      SIGNAL(signal_openBoundingBoxDialog(const unsigned int)),
                      this,
                      SLOT(slot_openBoundingBoxDialog(const unsigned int))
                      );

        this->connect(this->frameScene,
                      SIGNAL(signal_addBoundingBoxToCore(const Rect)),
                      this,
                      SLOT(slot_addBoundingBoxToCore(const Rect))
                      );

        this->connect(this->frameScene,
                      SIGNAL(signal_moveBoundingBoxInCore(const unsigned int, const Rect)),
                      this,
                      SLOT(slot_moveBoundingBoxInCore(const unsigned int, const Rect))
                      );

        this->connect(this->frameScene,
                      SIGNAL(signal_removeBoundingBoxFromCore(const unsigned int)),
                      this,
                      SLOT(slot_removeBoundingBoxFromCore(const unsigned int))
                      );

        this->connect(this,
                      SIGNAL(signal_drawFrameBboxes(const Frame)),
                      this->frameScene,
                      SLOT(slot_drawFrameBboxes(const Frame))
                      );

        // Loading name from file
        string stdName = videoName.toStdString();
        size_t slashFound = stdName.find_last_of("/");
        this->corePath = QString::fromStdString("./temp_" + stdName.substr(slashFound).substr(1) +".json");
        this->loaded = true;
        this->manager->loadVideo(videoName);
        this->totalFrames = std::round(+this->manager->getTotalFrames());

        // Lazy instantiation of SSAT Core
        if(this->singleton == NULL)
        {
            this->singleton = Core::getInstance(static_cast<unsigned int>(this->totalFrames));
            this->singleton->updateFrameId();
        }
        else
        {
            this->singleton->reset(static_cast<unsigned int>(this->totalFrames));
            this->singleton->updateFrameId();
        }
        this->frameScene->setSingleton(*(this->singleton));

        // Displaying Frame and Core information on Interface
        this->tableModel->setFrameBasedData(this->singleton->frameData);
        this->ui->sliderFrame->setRange(1, static_cast<int>(this->totalFrames));
        this->ui->tableViewFrame->setModel(this->tableModel);
        this->enableWidgets(true);
        this->updateFrame(1);

        this->messageRestoreJson();
        this->saveTimer->start(20000);
    }
}

void MainWindow::slot_backupJson()
{
    this->manager->exportJSON(*(this->singleton), this->corePath);
    std::cout << "User modifications were saved to file." << std::endl;
}

void MainWindow::slot_importJson()
{
    if(this->ui->actionImport_JSON->isEnabled())
    {
        QString jsonName = QFileDialog::getOpenFileName(this,
                                                        tr("Import JSON..."),
                                                        tr(QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString().c_str()),
                                                        tr("JSON file (*.json)"));
        this->manager->importJSON(*(this->singleton), this->tableModel, jsonName);
    }
    this->updateFrame(1);
}

void MainWindow::slot_exportJson()
{
    if(this->ui->actionExport_JSON->isEnabled())
    {
        QString jsonName = QFileDialog::getSaveFileName(this,
                                                        tr("Export JSON..."),
                                                        tr(QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString().c_str()),
                                                        tr("JSON file (*.json)"));
        this->manager->exportJSON(*(this->singleton), jsonName);
    }
}

void MainWindow::slot_closeApplitacion()
{
    QCoreApplication::quit();
}

void MainWindow::slot_openAttributesDialog()
{
    this->annotationDialog = new DialogAnnotation(this);
    this->annotationDialog->slot_initializeDialog(*(this->singleton));
    this->annotationDialog->setModal(true);
    this->annotationDialog->show();
}

void MainWindow::slot_openBoundingBoxDialog(const unsigned int _bboxKey)
{
    this->boundingBoxDialog = new DialogBoundingBox(this);
    this->connect(this->boundingBoxDialog,
                  SIGNAL(signal_updateFrame()),
                  this,
                  SLOT(slot_updateFrame())
                );

    unsigned long currentFrameId = static_cast<unsigned long>(this->manager->getFrameId() - 1);
    this->boundingBoxDialog->setModal(true);
    this->boundingBoxDialog->slot_initializeDialog(*(this->singleton), currentFrameId, _bboxKey);
    this->boundingBoxDialog->show();
}

void MainWindow::slot_slideVideo(int _frameId)
{
    std::cout << _frameId << std::endl;
    this->updateFrame(_frameId);
    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(_frameId);
    }
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

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }

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

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }
}

void MainWindow::slot_backButtonPressed()
{
    int nextFrameId = static_cast<int>(this->manager->getFrameId());

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }

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

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }
}

void MainWindow::slot_forwardButtonPressed()
{
    int nextFrameId = static_cast<int>(this->manager->getFrameId());

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }

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

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }
}

void MainWindow::slot_fastfButtonPressed()
{
    int nextFrameId = static_cast<int>(this->manager->getFrameId());

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }

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

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }
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

void MainWindow::slot_tableviewFrameSingleClicked(const QModelIndex _index){
    this->enableFrameBased(true);
    this->slot_initializeFrameBasedComboBox(_index);
}

void MainWindow::slot_tableViewFrameDoubleClicked(const QModelIndex _index)
{
    FrameBasedData data = this->singleton->frameData.at(_index.row());
    this->updateFrame(data.getInitialFrameId());
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

    if(this->frameBasedIsEnable)
    {
        this->ui->spinBoxFinalFrame->setValue(nextFrameId);
    }
}

void MainWindow::slot_updateFrame()
{
    int currentFrameId = static_cast<int>(this->manager->getFrameId() - 1);
    this->updateFrame(currentFrameId);
}

void MainWindow::slot_viewFrameContextMenu(const QPoint &_point)
{
    QPoint position = this->ui->viewFrame->mapToGlobal(_point);

    QMenu contextMenu;
    if (!this->isPlaying())
    {
        if(this->frameScene->selectedBBox().size() == 0)
        {
            contextMenu.addAction("New Bounding box\tCtrl+B", this, SLOT(slot_viewFrameNewBoxMenu()));
            contextMenu.addAction("New Frame box\tCtrl+F", this, SLOT(slot_viewFrameNewFrameMenu()));
        }
        else if(this->frameScene->selectedBBox().size() == 1)
        {
            contextMenu.addAction("Replicate Bounding box 10x", this, SLOT(slot_viewFrameReplicateBoxMenu10()));
            contextMenu.addAction("Replicate Bounding box 100x", this, SLOT(slot_viewFrameReplicateBoxMenu100()));
            contextMenu.addAction("Replicate Bounding box 10x back", this, SLOT(slot_viewFrameReplicateBoxMenu10back()));
            contextMenu.addAction("Remove Bounding box", this, SLOT(slot_viewFrameRemoveBoxMenu()));
        }
        contextMenu.exec(position);
    }
}

void MainWindow::slot_viewFrameNewBoxMenu()
{
    if (this->isPlaying() == false)
    {
        this->frameScene->slot_enableDraw();
    }
}

void MainWindow::slot_viewFrameNewFrameMenu()
{
    this->enableFrameBased(true);

    this->slot_initializeFrameBasedComboBox();

    this->manipulation = mode::insert;

    this->frameId = this->ui->sliderFrame->value();
    this->totalFrames = this->singleton->frames.size();

    this->ui->spinBoxInitialFrame->setMinimum(1);
    this->ui->spinBoxInitialFrame->setMaximum(static_cast<int>(this->totalFrames));
    this->ui->spinBoxFinalFrame->setMinimum(this->getIniFrameValue());
    this->ui->spinBoxFinalFrame->setMaximum(static_cast<int>(this->totalFrames));

    this->initializeComboboxes();

    this->ui->spinBoxInitialFrame->setValue(this->frameId);
    this->ui->spinBoxFinalFrame->setValue(this->frameId);
}

void MainWindow::slot_viewFrameReplicateBoxMenu10()
{
    qDebug() << "Repeat for " << 10 << " frames";
    vector<unsigned int> bboxKeys = this->frameScene->selectedBBox();
    for(int index = 0; index < bboxKeys.size(); index++)
    {
        this->slot_replicateBoundingBoxFromCore(bboxKeys[index], 10);
    }
}

void MainWindow::slot_viewFrameReplicateBoxMenu10back()
{
    qDebug() << "Repeat backwards for " << 10 << " frames";
    vector<unsigned int> bboxKeys = this->frameScene->selectedBBox();
    for(int index = 0; index < bboxKeys.size(); index++)
    {
        this->slot_replicateBoundingBoxFromCoreBackwards(bboxKeys[index], 10);
    }
}

void MainWindow::slot_viewFrameReplicateBoxMenu100()
{
    qDebug() << "Repeat for " << 100 << " frames";
    vector<unsigned int> bboxKeys = this->frameScene->selectedBBox();
    for(int index = 0; index < bboxKeys.size(); index++)
    {
        this->slot_replicateBoundingBoxFromCore(bboxKeys[index], 100);
    }
}

void MainWindow::slot_viewFrameRemoveBoxMenu()
{
    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setText("Any occurence of this bounding box in the following frames is going to be removed.");
    message.setInformativeText("Are you sure you want to continue?");
    message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    int response = message.exec();

    switch(response)
    {
    case QMessageBox::Yes:
        vector<unsigned int> bboxKeys = this->frameScene->selectedBBox();
        for(int index = 0; index < bboxKeys.size(); index++)
        {
            this->slot_removeBoundingBoxFromCore(bboxKeys[index]);
        }
    }
}

void MainWindow::slot_tableViewContextMenu(const QPoint &_point)
{
    if((this->tableModel) && (this->tableModel->rowCount() > 0))
    {
        QPoint tablePos = this->ui->tableViewFrame->mapTo(this->ui->tableViewFrame, _point);
        QPoint windowPos = this->ui->tableViewFrame->mapToGlobal(_point);
        QModelIndex index = this->ui->tableViewFrame->indexAt(tablePos);

        if((index.row() >= 0) && (index.row() < this->tableModel->rowCount()))
        {
            QMenu contextMenu;
            contextMenu.addAction("Change Annotation", this, SLOT(slot_tableViewChangeAnnotation()));
            contextMenu.addAction("Delete Annotation", this, SLOT(slot_tableViewRemoveAnnotation()));
            contextMenu.exec(windowPos);
        }
    }
}

void MainWindow::slot_tableViewChangeAnnotation()
{
    this->enableFrameBased(true);
    QModelIndex index = this->ui->tableViewFrame->currentIndex();
    this->slot_tableViewFrameDoubleClicked(index);
}

void MainWindow::slot_tableViewRemoveAnnotation()
{
    int response;
    QModelIndex index = this->ui->tableViewFrame->currentIndex();

    QMessageBox message;
    message.setIcon(QMessageBox::Warning);
    message.setText("Remove Annotation");
    message.setInformativeText("Are you sure you want to continue?");
    message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    response = message.exec();

    switch(response)
    {
    case QMessageBox::Yes:
        this->tableModel->removeRow(index.row());
        break;
    case QMessageBox::No:
        break;
    }
}

void MainWindow::slot_frameBasedInsertAccepted(const FrameBasedData _data)
{
    this->tableModel->insertRow(_data);
    //this->ui->tableViewFrame->horizontalHeader()->setSortIndicator(0, Qt::AscendingOrder);
    this->ui->tableViewFrame->setSortingEnabled(true);
    this->ui->tableViewFrame->sortByColumn(0, Qt::AscendingOrder);
}

void MainWindow::slot_frameBasedAlterAccepted(const FrameBasedData _data, const int _index)
{
    FrameBasedData data = this->singleton->frameData.at(static_cast<unsigned long>(_index));
    data.setCategory(this->ui->comboBoxCategory->currentText().toStdString());
    this->tableModel->changeRow(_data, _index);
}

void MainWindow::slot_on_sectionClicked(int _index)
{
    emit signal_sortTable(_index);
}

void MainWindow::slot_resizeFrame()
{
    if(!this->isPlaying())
    {
        int frame = static_cast<int>(this->manager->getFrameId());
        this->updateFrame(frame - 1);
    }
}

//-------------------------------------------------------------------------------------------------------------------

void MainWindow::slot_buttonBoxAccepted()
{
    FrameBasedData data = FrameBasedData(this->ui->comboBoxCategory->currentText().toStdString(),
                                         this->ui->lineEditInfo->text().toStdString(),
                                         this->ui->comboBoxLabel->currentText().toStdString(),
                                         std::string(),
                                         this->ui->spinBoxInitialFrame->value(),
                                         this->ui->spinBoxFinalFrame->value()
                                         );

    if(this->manipulation == mode::insert)
    {
        emit this->signal_frameBasedInsertAccepted(data);
    }
    else if(this->manipulation == mode::alter)
    {
        emit this->signal_frameBasedAlterAccepted(data, this->indexId);
    }

    this->enableFrameBased(false);
}

void MainWindow::slot_buttonBoxRejected()
{
    this->enableFrameBased(false);
}

void MainWindow::slot_lineEditInfoChanged()
{
    this->enableDisableButtonBox();
}

void MainWindow::slot_spinBoxValueChanged()
{
    this->enableDisableButtonBox();
}

void MainWindow::slot_initializeFrameBasedComboBox()
{
    this->manipulation = mode::insert;

    this->frameId = this->ui->spinBoxFinalFrame->value();
    this->totalFrames = static_cast<int>(this->singleton->frames.size());

    this->ui->spinBoxInitialFrame->setMinimum(1);
    this->ui->spinBoxInitialFrame->setMaximum(static_cast<int>(this->totalFrames));
    this->ui->spinBoxFinalFrame->setMinimum(this->getIniFrameValue());
    this->ui->spinBoxFinalFrame->setMaximum(static_cast<int>(this->totalFrames));

    this->initializeComboboxes();

    this->ui->spinBoxInitialFrame->setValue(this->frameId);
    this->ui->spinBoxFinalFrame->setValue(this->frameId);
}

void MainWindow::slot_initializeFrameBasedComboBox(const QModelIndex _index)
{
    this->manipulation = mode::alter;

    this->indexId = _index.row();
    this->totalFrames = static_cast<int>(this->singleton->frames.size());

    FrameBasedData frameData = this->singleton->frameData.at(static_cast<unsigned long>(_index.row()));

    this->ui->spinBoxInitialFrame->setMinimum(1);
    this->ui->spinBoxInitialFrame->setMaximum(static_cast<int>(this->totalFrames));
    this->ui->spinBoxFinalFrame->setMinimum(1);
    this->ui->spinBoxFinalFrame->setMaximum(static_cast<int>(this->totalFrames));

    this->initializeComboboxes(QString::fromStdString(frameData.getCategory()));

    this->ui->lineEditInfo->setText(QString::fromStdString(frameData.getInfo()));
    this->ui->comboBoxCategory->setCurrentText(QString::fromStdString(frameData.getCategory()));
    this->ui->comboBoxLabel->setCurrentText(QString::fromStdString(frameData.getLabel()));
    this->ui->spinBoxInitialFrame->setValue(frameData.getInitialFrameId());
    this->ui->spinBoxFinalFrame->setValue(frameData.getFinalFrameId());
}

void MainWindow::slot_comboBoxCategoryActivated(const QString &_text)
{
    QStringList labelList;
    QSet<QString> labelSet;

    // populate comboBoxLabel
    string category = _text.toStdString();
    multimap<string, string>::iterator it;
    for(it = this->singleton->attributes.lower_bound(category);
        it != this->singleton->attributes.upper_bound(category);
        it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);
}

unsigned int MainWindow::slot_addBoundingBoxToCore(const Rect _box)
{
    unsigned int currentFrameId = static_cast<unsigned int>(this->manager->getFrameId() - 1);
    unsigned int largestId = this->singleton->getLargestId() + 1;

    unsigned int latestKey = this->singleton->frames[currentFrameId].addBox(largestId, _box);

    this->singleton->setLatestKey(latestKey);
    this->singleton->setLatestId(largestId);
    this->singleton->setLargestId(largestId);

    this->updateFrame(currentFrameId);

    return latestKey;
}

void MainWindow::slot_editBoundingBoxInCore(const BoundingBox _bbox)
{
    unsigned long nextFrameId = static_cast<unsigned long>(this->manager->getFrameId());
}

void MainWindow::slot_moveBoundingBoxInCore(const unsigned int _bboxKey, const Rect _box)
{
    unsigned long currentFrameId = static_cast<unsigned long>(this->manager->getFrameId() - 1);
    this->singleton->frames[currentFrameId].setBox(_bboxKey, _box);

    BoundingBox focusBox = this->singleton->frames[currentFrameId].getBoxByKey(_bboxKey);
    if (this->ui->actionInterpolation->isChecked())
    {
        this->manager->exponentialForget(*(this->singleton), focusBox, currentFrameId, 10);
    }
}

void MainWindow::slot_replicateBoundingBoxFromCore(const unsigned int _bboxKey, const unsigned int _numFrames)
{
    unsigned int frameLimit = std::min(static_cast<unsigned int>(this->manager->getFrameId() + _numFrames),
                                       static_cast<unsigned int>(this->singleton->frames.size()));

    this->manager->replicateBoundingBoxFromCore(*(this->singleton), _bboxKey, _numFrames);
    this->updateFrame(frameLimit - 1);
}

void MainWindow::slot_replicateBoundingBoxFromCoreBackwards(const unsigned int _bboxKey, const unsigned int _numFrames)
{
    unsigned int frameLimit = std::max(static_cast<int>(this->manager->getFrameId() - _numFrames), 1);

    this->manager->replicateBoundingBoxFromCoreBackwards(*(this->singleton), _bboxKey, _numFrames);
    this->updateFrame(frameLimit);
}

void MainWindow::slot_removeBoundingBoxFromCore(const unsigned int _bboxKey)
{
    unsigned int currentFrameId = static_cast<unsigned int>(this->manager->getFrameId()) - 1;
    this->manager->removeBoxSequenceFromCore(*(this->singleton), _bboxKey);
    this->updateFrame(currentFrameId);
}

