#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "workerthread.h"

class VideoManager : public QObject
{
private:
    QThread thread;
    WorkerThread *worker;

public:
    ///
    /// \brief VideoManager Default constructor
    ///
    VideoManager();

    ///
    /// \brief ~VideoManager Default destructor
    ///
    ~VideoManager();

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
    /// \param _singleton Singleton containing annotation info
    /// \param _jsonName Name of the json that will receive the info
    ///
    void exportJSON(Core &_singleton, const QString &_jsonName);

    ///
    /// \brief importJSON Import a file from disk
    /// \param _singleton singleton that will receive the info
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
    /// \param _singleton Object to strore the new segment
    /// \param _data data to be inserted
    ///
    void insertFrameBasedSegment(Core &_singleton, const FrameBasedData &_data);

    ///
    /// \brief alterFrameBasedSegment Modify an existing frame based segment
    /// \param _singleton Object that contains the segment to be modified
    /// \param _data New data
    /// \param _index Index of data to be modified
    ///
    void alterFrameBasedSegment(Core &_singleton, const FrameBasedData &_data, const int _index);

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
