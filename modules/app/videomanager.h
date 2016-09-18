#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <QThread>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::Mat;
using cv::VideoCapture;

#include "workerthread.h"

class VideoManager
{
private:
    QThread thread;
    WorkerThread *worker;

public:
    VideoManager();
    ~VideoManager();

    Mat getFrame();
    Mat getFrame(unsigned int _frame);

    double getTotalFrames();
    void loadVideo(QString _path);
};

#endif // VIDEOMANAGER_H
