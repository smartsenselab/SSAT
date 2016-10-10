#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include "workerthread.h"

class VideoManager : public QObject
{
private:
    QThread thread;
    WorkerThread *worker;

signals:
    void signal_frameToDisplay(const QImage _frame);
    void signal_positionToMove(const double _frameId);

public:
    VideoManager();
    ~VideoManager();

    Mat getFrame();
    Mat getFrame(double _frameId);
    double getFrameId();
    double getTotalFrames();
    double getVideoFPS();
    double getPercentage();
    int getTime();

    bool isPlaying();
    void isPlaying(bool _condition);

    void clearVideo();
    void loadVideo(const QString _path);
    QImage matToQimage(const Mat &_frame);
};

#endif // VIDEOMANAGER_H
