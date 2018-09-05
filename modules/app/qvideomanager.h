#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "qworkerthread.h"

class QVideoManager : public QObject
{
private:
    QThread thread;
    QWorkerThread *worker;

public:
    ///
    /// \brief VideoManager Default constructor
    ///
    QVideoManager();

    ///
    /// \brief ~VideoManager Default destructor
    ///
    ~QVideoManager();

    ///
    /// \brief getFrame Get the next frame from video
    /// \return The frame
    ///
    Mat getFrame();

    ///
    /// \brief getFrame Get a specific frame from video
    /// \param _frameId Id of the required frame
    /// \return  The frame
    ///
    Mat getFrame(double _frameId);

    ///
    /// \brief getFrameId get the current frame Id
    /// \return  The frame Id
    ///
    double getFrameId();

    ///
    /// \brief getTotalFrames Get the total number of frames
    /// \return  Total number of frames
    ///
    double getTotalFrames();

    ///
    /// \brief getVideoFPS Get the frameRate
    /// \return FrameRate
    ///
    double getVideoFPS();

    ///
    /// \brief getPercentage get percentage of the videos that has been played
    /// \return Percentage played
    ///
    double getPercentage();

    ///
    /// \brief getTime Get the video time
    /// \return  Video Time
    ///
    int getTime();

    ///
    /// \brief isPlaying Return if video is playing
    /// \return true for playing and false for not playing
    ///
    bool isPlaying();

    ///
    /// \brief isPlaying Change the state of the video
    /// \param _condition true to play the video false to stop playing
    ///
    void isPlaying(bool _condition);

    ///
    /// \brief clearVideo
    ///
    void clearVideo();

    ///
    /// \brief loadVideo Load a new video
    /// \param _path Path to the folder where the video is
    ///
    void loadVideo(const QString _path);

    ///
    /// \brief exportJSON Export work done to a json file
    /// \param _singleton Core that contains all the annotation information
    /// \param _jsonName Name of the json that will receive the info
    ///
    void exportJSON(Core &_singleton, const QString &_jsonName);

    ///
    /// \brief importJSON Import a file from disk
    /// \param _singleton Core that contains all the annotation information
    /// \param _tableModel Table of mainwindow that show the data
    /// \param _jsonName name of file to be imported
    ///
    void importJSON(Core &_singleton, QFrameBasedTableModel *_tableModel, const QString &_jsonName);

    ///
    /// \brief matToQimage Tranform an opencv mat to a Qimage
    /// \param _frame Image to be transformed
    /// \return  Qimage already transformed
    ///
    QImage matToQimage(const Mat &_frame);

    ///
    /// \brief insertFrameBasedSegment Create a new frame based segment
    /// \param _singleton Core that contains all the annotation information
    /// \param _data data to be inserted
    ///
    void insertFrameBasedSegment(Core &_singleton, const FrameBasedData &_data);

    ///
    /// \brief alterFrameBasedSegment Modify an existing frame based segment
    /// \param _singleton Core that contains all the annotation information
    /// \param _data New data
    /// \param _index Index of data to be modified
    ///
    void alterFrameBasedSegment(Core &_singleton, const FrameBasedData &_data, const int _index);

    ///
    /// \brief exponentialForget Smoothes a BBox throughtout following whenever the user moves or resizes it
    /// \param _singleton Core that contains all the annotation information
    /// \param _focusBox BBox that must be replicated in the following frames
    /// \param _frameId Frame corresponding to the focused bounding box
    /// \param _numFrames Number of frames that must include the transformation
    ///
    void exponentialForget(Core &_singleton, const BoundingBox _focusBox, const unsigned int _frameId, const unsigned int _numFrames = 25);

    ///
    /// \brief replicateBoundingBoxFromCore Replicate current bounding box in the following frames
    /// \param _singleton Core that contains all the annotation information
    /// \param _bboxKey key indicating the correct bounding box
    /// \param _numFrames Number of frames that will receive the bounding box
    ///
    void replicateBoundingBoxFromCore(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames = 10);

    ///
    /// \brief replicateBoundingBoxFromCoreBackwards Replicate current bounding box in the previous frames
    /// \param _singleton Core that contains all the annotation information
    /// \param _bboxKey key indicating the correct bounding box
    /// \param _numFrames Number of frames that will receive the bounding box
    ///
    void replicateBoundingBoxFromCoreBackwards(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames);

    ///
    /// \brief removeBoxSequenceFromCore Delete a BBox from current and following frames
    /// \param _singleton Core that contains all the annotation information
    /// \param _bboxKey key indicating the correct bounding box
    ///
    void removeBoxSequenceFromCore(Core &_singleton, const unsigned int _bboxKey);

signals:
    ///
    /// \brief signal_frameToDisplay signal wich frame will be displayed
    /// \param _frame Frame to display
    ///
    void signal_frameToDisplay(const QImage _frame);

    ///
    /// \brief signal_positionToMove Signal position to move
    /// \param _frameId Wich frame to jump to
    ///
    void signal_positionToMove(const double _frameId);
};

#endif // VIDEOMANAGER_H
