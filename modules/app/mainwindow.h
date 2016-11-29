#ifndef mainwindow_h
#define mainwindow_h

#include<QShortcut>
#include <iostream>
#include<QProgressDialog>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMessageBox>
#include <QScopedPointer>
#include <QTime>
#include <QTimer>

#include "dialogannotation.h"
#include "dialogframebased.h"
#include "framebaseddata.h"
#include "qboundingbox.h"
#include "qframebasedtablemodel.h"
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

    QImage frameQImage;
    QTimer *playerTime = NULL;

    Core *singleton = NULL;

    DialogAnnotation *annotationDialog = NULL;
    DialogFrameBased *frameDialog = NULL;

    QBoundingBox frameScene;
    QFrameBasedTableModel *tableModel = NULL;
    QGraphicsRectItem *rectangle = NULL;

    VideoManager *manager;

    QString nome;
    int InitFrame;
    int EndFrame;

public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    QProgressDialog *m_progress;
    QAction *crtf = new QAction(tr("id1"),this);
    QAction *crto = new QAction(tr("id"),this);
    QAction *crti = new QAction(tr("id2"),this);
    QAction *crte = new QAction(tr("id3"),this);
    QAction *crta = new QAction(tr("id4"),this);
    QAction *crtb = new QAction(tr("id5"),this);
protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void enableWidgets(const bool _enable);
    void connectSignalSlots();
    void setTableModel();

    bool isPlaying();
    void isPlaying(const bool _enable);

    void changeSpeed(const int _speed);
    void pauseVideo();
    void playVideo();
    void stopVideo();
    void updateFrame();
    void updateFrame(const int _frameId);

    void connectMainWindow2DialogFrameBased();

public slots:
    void Fshortcut();
    void Ashortcut();
    void Oshortcut();
    void Ishortcut();
    void Bshortcut();
    void Eshortcut();
    void slot_displayFrame(const QImage _frame);
    void slot_openFile();
    void slot_importJson();
    void slot_importProgressBar();
    void slot_exportJson();
    void slot_closeApplitacion();
    void slot_openAttributes();

    void slot_slideVideo(int _frameId);

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
    void slot_tableViewFrameDoubleClicked(const QModelIndex _index);

    void slot_keepVideoRunning();

    void slot_viewFrameContextMenu(const QPoint &_point);
    void slot_viewFrameNewBoxMenu();
    void slot_viewFrameNewFrameMenu();
    void slot_viewFrameRemoveBoxMenu();
    void slot_tableViewContextMenu(const QPoint &_point);
    void slot_tableViewChangeAnnotation();
    void slot_tableViewRemoveAnnotation();

    void slot_frameBasedInsertAccepted(const FrameBasedData _data);
    void slot_frameBasedAlterAccepted(const FrameBasedData _data, const int _index);

    void slot_addBoundingBoxToCore(const Rect _box);

signals:
    void signal_drawFrameBboxes(const Frame _frame);
};

#endif
