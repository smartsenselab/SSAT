#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->frameScene = new QBoundingBox;
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
                  &MainWindow::slot_openAttributes
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

    // Connecting custom SIGNALS to SLOTS
    this->connect(this->saveTimer,
                  SIGNAL(timeout()),
                  SLOT(slot_backupJson())
                  );

    this->connect(this->frameScene,
                  SIGNAL(signal_addBoundingBoxToCore(const Rect)),
                  this,
                  SLOT(slot_addBoundingBoxToCore(const Rect))
                  );

    this->connect(this,
                  SIGNAL(signal_drawFrameBboxes(const Frame)),
                  (this->frameScene),
                  SLOT(slot_drawFrameBboxes(const Frame))
                  );

    this->connect(this->ui->splitterHorizontal,
                  SIGNAL(splitterMoved(int,int)),
                  this,
                  SLOT(slot_resizeFrame())
                  );
}

void MainWindow::setShortcuts()
{
    this->crta = new QAction(tr("id1"), this);
    this->crtb = new QAction(tr("id2"), this);
    this->crte = new QAction(tr("id3"), this);
    this->crtf = new QAction(tr("id4"), this);
    this->crti = new QAction(tr("id5"), this);
    this->crto = new QAction(tr("id6"), this);
    this->crtw = new QAction(tr("id7"), this);

    this->crta->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_A);
    this->crtb->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_B);
    this->crte->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_E);
    this->crtf->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_F);
    this->crti->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_I);
    this->crto->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_O);
    this->crtw->setShortcuts(QList<QKeySequence>() << Qt::CTRL + Qt::Key_W);

    this->addAction(crta);
    this->addAction(crtb);
    this->addAction(crte);
    this->addAction(crtf);
    this->addAction(crti);
    this->addAction(crto);
    this->addAction(crtw);

    // Connecting SHORTCUTS to SLOTS
    this->connect(this->crta, SIGNAL(triggered()), SLOT(slot_Ashortcut()));
    this->connect(this->crtb, SIGNAL(triggered()), SLOT(slot_Bshortcut()));
    this->connect(this->crte, SIGNAL(triggered()), SLOT(slot_Eshortcut()));
    this->connect(this->crtf, SIGNAL(triggered()), SLOT(slot_Fshortcut()));
    this->connect(this->crti, SIGNAL(triggered()), SLOT(slot_Ishortcut()));
    this->connect(this->crto, SIGNAL(triggered()), SLOT(slot_Oshortcut()));
    this->connect(this->crtw, SIGNAL(triggered()), SLOT(slot_Wshortcut()));
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
    Mat frameMat = this->manager->getFrame();
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
    Mat frameMat = this->manager->getFrame(_frameId + this->speed);
    unsigned long nextFrameId = static_cast<unsigned long>(this->manager->getFrameId());

    if(frameMat.data)
    {
        this->ui->sliderFrame->setValue(static_cast<int>(_frameId));
        this->ui->labelFrameId->setText(QString::number(_frameId) + "/" + QString::number(this->totalFrames));

        this->frameScene->clear();

        qint64 current = this->manager->getTime();
        QTime currentTime((current/3600)%60, (current/60)%60, current%60, (current*1000)%1000);
        QString stringTime = currentTime.toString("hh:mm:ss");
        this->ui->labelTime->setText(stringTime);

        this->frameQImage = this->manager->matToQimage(frameMat);
        this->frameScene->addPixmap(QPixmap::fromImage(frameQImage));

        this->ui->viewFrame->setScene((this->frameScene));
        this->ui->viewFrame->fitInView(this->frameScene->sceneRect(), Qt::KeepAspectRatio);

        emit signal_drawFrameBboxes(this->singleton->frames[static_cast<unsigned long>(nextFrameId - 1)]);
    }
}

void MainWindow::restoreJson()
{
    std::ifstream file(this->core_path.toStdString());
    if (file.good())
    {
        int response;
        QMessageBox message;
        message.setIcon(QMessageBox::Warning);
        message.setText("There is a backup file in your directory.");
        message.setInformativeText("Do you want to restore previous settings");
        message.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        response = message.exec();

        switch(response)
        {
        case QMessageBox::Yes:
            this->manager->importJSON(*(this->singleton), this->tableModel, this->core_path);
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
    this->slot_openAttributes();
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
                                                     tr("/home"),
                                                     tr("Video Files (*.avi *.mp4 *.mov)"));


    if(!videoName.isEmpty())
    {
        if(this->oneVideoWasOpened == 1)
        {
            this->tableModel->clear();
        }
        else
        {
            this->oneVideoWasOpened = 1;
        }

        delete this->frameScene;
        this->frameScene = new QBoundingBox;

        string temp = videoName.toStdString();
        size_t found = temp.find_last_of("/");
        this->core_path =QString::fromStdString( "./temp_" + temp.substr(found).substr(1) +".json");
        this->loaded = true;
        this->manager->loadVideo(videoName);
        this->totalFrames = std::round(+this->manager->getTotalFrames());

        if(this->singleton == NULL)
        {
            this->singleton = Core::getInstance(static_cast<unsigned int>(this->totalFrames));
        }
        else
        {
            this->singleton->reset(static_cast<unsigned int>(this->totalFrames));
        }

        this->tableModel->setFrameBasedData(this->singleton->frameData);
        this->ui->sliderFrame->setRange(1, static_cast<int>(this->totalFrames));
        this->ui->tableViewFrame->setModel(this->tableModel);
        this->enableWidgets(true);
        this->updateFrame(1);

        this->restoreJson();
        this->saveTimer->start(10000);
    }
}

void MainWindow::slot_backupJson()
{

    this->manager->exportJSON(*(this->singleton), this->core_path);
    std::cout << "saving" << std::endl;
}

void MainWindow::slot_importJson()
{
    if(this->ui->actionImport_JSON->isEnabled())
    {
        QString jsonName = QFileDialog::getOpenFileName(this,
                                                        tr("Import JSON..."),
                                                        tr("/home"),
                                                        tr("JSON file (*.json)"));
        this->manager->importJSON(*(this->singleton), this->tableModel, jsonName);
    }
}

void MainWindow::slot_exportJson()
{
    if(this->ui->actionExport_JSON->isEnabled())
    {
        QString jsonName = QFileDialog::getSaveFileName(this,
                                                        tr("Export JSON..."),
                                                        tr("/home"),
                                                        tr("JSON file (*.json)"));
        this->manager->exportJSON(*(this->singleton), jsonName);
    }
}

void MainWindow::slot_closeApplitacion()
{
    QCoreApplication::quit();
}

void MainWindow::slot_openAttributes()
{
    this->annotationDialog = new DialogAnnotation(this);
    this->annotationDialog->slot_initializeDialog(*(this->singleton));
    this->annotationDialog->setModal(true);
    this->annotationDialog->show();
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
    this->slot_initializeDialog(_index);
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

void MainWindow::slot_viewFrameContextMenu(const QPoint &_point)
{
    QPoint position = this->ui->viewFrame->mapToGlobal(_point);

    QMenu contextMenu;
    if (!this->isPlaying())
    {
        contextMenu.addAction("New Bounding box     Ctrl+B", this, SLOT(slot_viewFrameNewBoxMenu()));
        contextMenu.addAction("New Frame box          Ctrl+F", this, SLOT(slot_viewFrameNewFrameMenu()));
        contextMenu.addAction("Remove Bbox", this, SLOT(slot_viewFrameRemoveBoxMenu()));
        contextMenu.exec(position);
    }
}

void MainWindow::slot_viewFrameNewBoxMenu()
{
    if (this->isPlaying() == false)
    {
        this->frameScene->slot_enableDraw();
    }

    //    // CheckBox
    //    QTableWidgetItem *checkBoxItem = new QTableWidgetItem();
    //    checkBoxItem->setCheckState(Qt::Unchecked);

    //    // Cancel Button
    //    QPushButton* btn_cancel = new QPushButton();
    //    btn_cancel = new QPushButton();
    //    btn_cancel->setText("Cancel");
    //    //btn_cancel->setIcon(QIcon("https://t4.ftcdn.net/jpg/00/08/30/29/500_F_8302961_GVoPsXWcNsfvVygwE2sri9m9aISpJgYQ.jpg"));

    //    // Table row
    //    int row = this->ui->tableWidget->rowCount() - 1;
    //    this->ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    //    this->ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, checkBoxItem);
    //    this->ui->tableWidget->setCellWidget(row, 3, btn_cancel);
}

void MainWindow::slot_viewFrameNewFrameMenu()
{
    this->enableFrameBased(true);

    this->slot_initializeDialog();

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

void MainWindow::slot_viewFrameRemoveBoxMenu()
{
    this->frameScene->deleteBBox();
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
    FrameBasedData frameData = this->singleton->frameData.at(static_cast<unsigned long>(_index));
    frameData.setCategory(this->ui->comboBoxCategory->currentText().toStdString());
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
    FrameBasedData data = FrameBasedData(this->ui->spinBoxInitialFrame->value(),
                                         this->ui->spinBoxFinalFrame->value(),
                                         this->ui->comboBoxCategory->currentText().toStdString(),
                                         this->ui->comboBoxLabel->currentText().toStdString(),
                                         this->ui->lineEditInfo->text().toStdString());

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

void MainWindow::slot_initializeDialog()
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

void MainWindow::slot_initializeDialog(const QModelIndex _index)
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
    for(it = this->singleton->attributes.lower_bound(category); it != this->singleton->attributes.upper_bound(category); it++)
    {
        labelSet.insert(QString::fromStdString(it->second));
    }
    labelList.append(labelSet.toList());

    this->labelModel->setStringList(labelList);
    this->ui->comboBoxLabel->setModel(this->labelModel);
}

void MainWindow::slot_addBoundingBoxToCore(const Rect _box)
{
    unsigned long nextFrameId = static_cast<unsigned long>(this->manager->getFrameId());
    unsigned long num_bboxes = static_cast<unsigned long>(this->singleton->frames[nextFrameId - 1].getBoxes().size());

    string temp_id = "frame" + std::to_string(nextFrameId - 1);
    string temp_key = "bbox" + std::to_string(num_bboxes);

    this->singleton->frames[nextFrameId - 1].addBox(temp_id + "_" + temp_key, _box);
}

