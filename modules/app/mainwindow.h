#ifndef mainwindow_h
#define mainwindow_h

#include <cmath>
#include <iostream>
#include <fstream>

#include <QDialog>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QMessageBox>
#include <QProgressDialog>
#include <QScopedPointer>
#include <QShortcut>
#include <QTime>
#include <QTimer>

#include "core.h"

#include "dialogannotation.h"
#include "framebaseddata.h"
#include "qboundingboxscene.h"
#include "qframebasedtablemodel.h"
#include "videomanager.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QScopedPointer<Ui::MainWindow> ui;

    ///
    /// \brief crtX Shortcut for all actions
    ///
    QAction *crta = NULL;
    QAction *crtb = NULL;
    QAction *crte = NULL;
    QAction *crtf = NULL;
    QAction *crti = NULL;
    QAction *crto = NULL;
    QAction *crtw = NULL;

    bool loaded;
    bool playing;
    bool frameBasedIsEnable;
    double totalFrames;
    int speed;

    QImage frameQImage;
    QString corePath;
    QTimer *playerTime = NULL;
    QTimer *saveTimer = NULL;

    Core *singleton = NULL;
    DialogAnnotation *annotationDialog = NULL;
    QBoundingBoxScene *frameScene = NULL;
    QFrameBasedTableModel *tableModel = NULL;
    QGraphicsRectItem *rectangle = NULL;

    QString nome;
    QString videopath;

    QStringListModel *categoryModel = NULL;
    QStringListModel *labelModel = NULL;

    VideoManager *manager = NULL;

    // FrameBased:
    int frameId, indexId;
    mode manipulation;

public:
    ///
    /// \brief MainWindow   Prepare the view to be initialized
    /// \param parent
    ///
    MainWindow(QWidget *parent = 0);

    ///
    /// \brief ~MainWindow Default destructor
    ///
    virtual ~MainWindow();

protected:
    ///
    /// \brief keyPressEvent Shortcut to delete annotation
    /// \param event button 'Delete'
    ///
    void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

    ///
    /// \brief resizeEvent  Resize the window
    /// \param event
    ///
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    ///
    /// \brief enableWidgets Enable/Disable the buttons of the window
    /// \param _enable
    ///
    void enableWidgets(const bool _enable);

    ///
    /// \brief enableFrameBased Enable/Disable the box used to create or change annotation
    /// \param _enable
    ///
    void enableFrameBased(const bool _enable);

    ///
    /// \brief connectSignalSlots   Connect the sinals to a slot
    ///
    void connectSignalSlots();

    ///
    /// \brief setShortcuts Define the window's shortcut
    ///
    void setShortcuts();

    ///
    /// \brief setTableModel    Create the table design
    ///
    void setTableModel();

    ///
    /// \brief isPlaying    Return if the video is playing or not
    /// \return
    ///
    bool isPlaying();

    ///
    /// \brief isPlaying    Change the button to 'Play' or 'Pause'
    /// \param _enable
    ///
    void isPlaying(const bool _enable);

    ///
    /// \brief changeSpeed  Controls video speed
    /// \param _speed
    ///
    void changeSpeed(const int _speed);

    ///
    /// \brief pauseVideo   Pauses the video
    ///
    void pauseVideo();

    ///
    /// \brief playVideo    Plays the video
    ///
    void playVideo();

    ///
    /// \brief stopVideo    Stops the video
    ///
    void stopVideo();

    ///
    /// \brief updateFrame  Update the frame and time when it has changed (by slider, spin, etc)
    ///
    void updateFrame();

    ///
    /// \brief updateFrame  Update the frame, the next frame will be the param of this function
    /// \param _frameId     The number of the frame that will be the next frame
    ///
    void updateFrame(const int _frameId);

    ///
    /// \brief restoreJson  Get a Json file previously created (if the user wants to)
    ///
    void messageRestoreJson();

    ///
    /// \brief getIniFrameValue Return the initial frame of the annotation displayed on the interface
    /// \return
    ///
    int getIniFrameValue();

    ///
    /// \brief getEndFrameValue Return the final frame of the annotation displayed on the interface
    /// \return
    ///
    int getEndFrameValue();

    ///
    /// \brief getInfoValue Return the annotation information displayed on the interface
    /// \return
    ///
    QString getInfoValue();

    // FrameBased:
    ///
    /// \brief initializeComboboxes Build the multimap of the category and label
    ///
    void initializeComboboxes();

    ///
    /// \brief initializeComboboxes Add a new category
    /// \param _category    The QString (name) that will represent the category
    ///
    void initializeComboboxes(const QString _category);

    ///
    /// \brief enableDisableButtonBox   Enable and Disable the buttons 'Ok' and 'Cancel' of the annotation box
    ///
    void enableDisableButtonBox();

public slots:
    ///
    /// \brief slot_Fshortcut   Shortcut to open the annotation box
    ///
    void slot_Fshortcut();

    ///
    /// \brief slot_Ashortcut   Shortcut to open the annotation attributes
    ///
    void slot_Ashortcut();

    ///
    /// \brief slot_Oshortcut   Shortcut to open a new video
    ///
    void slot_Oshortcut();

    ///
    /// \brief slot_Ishortcut   Shortcut to import Json
    ///
    void slot_Ishortcut();

    ///
    /// \brief slot_Bshortcut   Shortcut to create a new BBox
    ///
    void slot_Bshortcut();

    ///
    /// \brief slot_Eshortcut   Shortcut to export Json
    ///
    void slot_Eshortcut();

    ///
    /// \brief slot_Wshortcut   Shortcut to close the app
    ///
    void slot_Wshortcut();

    ///
    /// \brief slot_displayFrame    Shows the actual frame
    /// \param _frame   Number of the frame
    ///
    void slot_displayFrame(const QImage _frame);

    ///
    /// \brief slot_openFile    Open a valid video
    ///
    void slot_openFile();

    ///
    /// \brief slot_backupJson  Export a backup Json file
    ///
    void slot_backupJson();

    ///
    /// \brief slot_importJson  Import a Json file
    ///
    void slot_importJson();

    ///
    /// \brief slot_exportJson Export a Json file
    ///
    void slot_exportJson();

    ///
    /// \brief slot_closeApplitacion    Ends the app
    ///
    void slot_closeApplitacion();

    ///
    /// \brief slot_openAttributes  Open the annotation attributes window
    ///
    void slot_openAttributes();

    ///
    /// \brief slot_slideVideo  Change the actual frame of the video
    /// \param _frameId Number of the frame that will be the next 'actual frame'
    ///
    void slot_slideVideo(int _frameId);

    ///
    /// \brief slot_playButtonPressed   Set the 'isPlaying' as true or false
    ///
    void slot_playButtonPressed();

    ///
    /// \brief slot_rewindButtonPressed Go back 1% of total number of frames
    ///
    void slot_rewindButtonPressed();

    ///
    /// \brief slot_rewindButtonPressed Auxiliar function to rewind the video
    /// \param _frameId The next frame
    ///
    void slot_rewindButtonPressed(const int _frameId);

    ///
    /// \brief slot_backButtonPressed Go back 1 frame
    ///
    void slot_backButtonPressed();

    ///
    /// \brief slot_backButtonPressed   Auxiliar function to go back 1 frame on the video
    /// \param _frameId the next frame (need to do _frameId - 2 to go back 1 frame)
    ///
    void slot_backButtonPressed(const int _frameId);

    ///
    /// \brief slot_forwardButtonPressed    Go foward 1 frame
    ///
    void slot_forwardButtonPressed();

    ///
    /// \brief slot_forwardButtonPressed    Auxiliar function to go foward 1 frame
    /// \param _frameId The next frame
    ///
    void slot_forwardButtonPressed(const int _frameId);

    ///
    /// \brief slot_fastfButtonPressed  Go foward 1% of total number of frames
    ///
    void slot_fastfButtonPressed();

    ///
    /// \brief slot_fastfButtonPressed  Auxiliar function to go foward 1% the video
    /// \param _frameId The next frame
    ///
    void slot_fastfButtonPressed(const int _frameId);

    ///
    /// \brief slot_stopButtonPressed   Stops the video
    ///
    void slot_stopButtonPressed();

    ///
    /// \brief slot_spinBoxSpeedValueChanged    Change the speed of the video
    /// \param _value   The valor that the speed will be multiplied
    ///
    void slot_spinBoxSpeedValueChanged(int _value);

    ///
    /// \brief slot_tableviewFrameSingleClicked Open the annotation box to chance a annotation
    /// \param _index   Identifies which annotation will be modified
    ///
    void slot_tableviewFrameSingleClicked(const QModelIndex _index);

    ///
    /// \brief slot_tableViewFrameDoubleClicked Open the annotation box to change a annotation
    /// \param _index   Identifies which annotation will be modified
    ///
    void slot_tableViewFrameDoubleClicked(const QModelIndex _index);

    ///
    /// \brief slot_keepVideoRunning    Blocks the user to create annotations or BBox while video is running
    ///
    void slot_keepVideoRunning();

    ///
    /// \brief slot_viewFrameContextMenu    A new menu appears when right mouse button is pressed
    /// \param _point
    ///
    void slot_viewFrameContextMenu(const QPoint &_point);

    ///
    /// \brief slot_viewFrameNewBoxMenu Enable create new BBox
    ///
    void slot_viewFrameNewBoxMenu();

    ///
    /// \brief slot_viewFrameNewFrameMenu   Starts to create a new annotation
    ///
    void slot_viewFrameNewFrameMenu();

    ///
    /// \brief slot_viewFrameRemoveBoxMenu  Remove a BBox
    ///
    void slot_viewFrameRemoveBoxMenu();

    ///
    /// \brief slot_tableViewContextMenu    A new menu appears when right mouse button is pressed on the table
    /// \param _point
    ///
    void slot_tableViewContextMenu(const QPoint &_point);

    ///
    /// \brief slot_tableViewChangeAnnotation   Annotation box is opened to be able to chance a annotation
    ///
    void slot_tableViewChangeAnnotation();

    ///
    /// \brief slot_tableViewRemoveAnnotation   Remove the annotation selected
    ///
    void slot_tableViewRemoveAnnotation();

    ///
    /// \brief slot_frameBasedInsertAccepted    Sucess creating a new annotation
    /// \param _data
    ///
    void slot_frameBasedInsertAccepted(const FrameBasedData _data);

    ///
    /// \brief slot_frameBasedAlterAccepted Sucess changing an annotation
    /// \param _data
    /// \param _index
    ///
    void slot_frameBasedAlterAccepted(const FrameBasedData _data, const int _index);

    ///
    /// \brief slot_on_sectionClicked   Sort the column clicked
    /// \param _index
    ///
    void slot_on_sectionClicked(int _index);

    ///
    /// \brief slot_resizeFrame Resize the frame
    ///
    void slot_resizeFrame();

    // FrameBased:
    ///
    /// \brief slot_buttonBoxAccepted   Insert or Change annotation succeed
    ///
    void slot_buttonBoxAccepted();

    ///
    /// \brief slot_buttonBoxRejected   Insert or Change annotation didn't succeed
    ///
    void slot_buttonBoxRejected();

    ///
    /// \brief slot_lineEditInfoChanged Enable/Disable button box
    ///
    void slot_lineEditInfoChanged();

    ///
    /// \brief slot_spinBoxValueChanged Enable/Disable button box
    ///
    void slot_spinBoxValueChanged();

    ///
    /// \brief slot_initializeDialog    Prepare the annotation box to be used to insert a new annotation
    ///
    void slot_initializeDialog();

    ///
    /// \brief slot_initializeDialog    Prepare the annotation box to be used to change a new annotation
    /// \param _index   The previous annotation
    ///
    void slot_initializeDialog(const QModelIndex _index);

    ///
    /// \brief slot_comboBoxCategoryActivated   Insert a new category
    /// \param _text
    ///
    void slot_comboBoxCategoryActivated(const QString &_text);

    // BoundingBox-Based
    ///
    /// \brief slot_addBoundingBoxToCore    Save the x,y,w,h of the BBox on core
    /// \param _box
    ///
    void slot_addBoundingBoxToCore(const Rect _box);

    ///
    /// \brief signal_moveBoundingBoxInCore Update core with new bbox position
    /// \param _frameId frame which bbox will be updated
    /// \param _bboxId  id of bounding box that will be updated
    ///
    void slot_moveBoundingBoxInCore(const unsigned int _frameId, const unsigned int _bboxId);

    ///
    /// \brief slot_removeBoundingBoxFromCore Remove bbox from core
    /// \param _frameId frame which bbox will be removed from
    /// \param _bboxId  id of bounding box that will be deleted
    ///
    void slot_removeBoundingBoxFromCore(const unsigned int _frameId, const unsigned int _bboxId);

signals:
    ///
    /// \brief signal_drawFrameBboxes   Signal to call slot_drawFrameBboxes
    /// \param _frame   Actual frame
    ///
    void signal_drawFrameBboxes(const Frame _frame);

    ///
    /// \brief signal_sortTable Signal to call slot_sortTable
    ///
    void signal_sortTable(int);

    // Frame-Based:
    ///
    /// \brief signal_buttonBoxAccepted to call nobody
    ///
    void signal_buttonBoxAccepted();

    ///
    /// \brief signal_frameBasedInsertAccepted Signal to call slot_frameBasedInsertAccepted
    /// \param _data    Informations of the annotation
    ///
    void signal_frameBasedInsertAccepted(const FrameBasedData _data);

    ///
    /// \brief signal_frameBasedAlterAccepted Signal to call slot_frameBasedAlterAccepted
    /// \param _data    Previous informations of the annotation
    /// \param _index   Number of the line
    ///
    void signal_frameBasedAlterAccepted(const FrameBasedData _data, const int _index);

    ///
    /// \brief signal_frameBasedRejected Signal to call nobody
    ///
    void signal_frameBasedRejected();
};

#endif
