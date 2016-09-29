#ifndef mainwindow_h
#define mainwindow_h

#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QScopedPointer>
#include <QTimer>

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

    QBoundingBox frameScene;
    QGraphicsRectItem *rectangle = NULL;
    QImage frameQImage;
    QTimer *playerTime = NULL;

    VideoManager *manager;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    void enableWidgets(const bool _enable);
    void connectSignalSlots();

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

    void slot_playButton();
    void slot_rewindButton();
    void slot_backButton();
    void slot_forwardButton();
    void slot_fastfButton();
    void slot_stopButton();
    void slot_spinBoxSpeed(int _value);

    void slot_keepVideoRunning();

    void slot_newBox();
};

#endif
