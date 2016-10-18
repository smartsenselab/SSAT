#ifndef mainwindow_h
#define mainwindow_h

#include <iostream>

#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QScopedPointer>
#include <QTime>
#include <QTimer>

#include "dialogframebased.h"
#include "qboundingbox.h"
#include "videomanager.h"

#include "core.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QScopedPointer<Ui::MainWindow> ui;

    bool loaded;
    bool playing;
    double totalFrames;
    int speed;

    Core *singleton = NULL;

    QBoundingBox frameScene;
    QGraphicsRectItem *rectangle = NULL;
    QImage frameQImage;
    QTimer *playerTime = NULL;
    DialogFrameBased *frameDialog = NULL;

    VideoManager *manager;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void enableWidgets(const bool _enable);
    void connectSignalSlots();
    void setTable();

    bool isPlaying();
    void isPlaying(const bool _enable);

    void changeSpeed(const int _speed);
    void pauseVideo();
    void playVideo();
    void stopVideo();
    void updateFrame();
    void updateFrame(const int _frameId);

public slots:
    void slot_displayFrame(const QImage _frame);
    void slot_openFile();
    void slot_slideVideo(int _frameId);
    void slot_contextMenu(const QPoint &_point);

    void slot_playButtonPressed();

    void slot_rewindButtonPressed();
    void slot_rewindButtonPressed(const int _frameId);
    void slot_backButtonPressed();
    void slot_backButtonPressed(const int _frameId);
    void slot_forwardButtonPressed();
    void slot_forwardButtonPressed(const int _frameId);
    void slot_fastfButtonPressed();
    void slot_fastfButtonPressed(const int _frameId);
    void slot_stopButtonPressed();
    void slot_spinBoxSpeedValueChanged(int _value);

    void slot_keepVideoRunning();

    void slot_newBoxMenu();
    void slot_newFrameMenu();
    void slot_removeBoxMenu();

    void slot_addFrameBbox(Rect _box);

signals:
    void signal_drawFrameBboxes(const Frame _frame);
};

#endif
