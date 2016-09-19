#ifndef VIDEOMANAGEMENT_H
#define VIDEOMANAGEMENT_H

#include <QObject>
#include <QThread>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::Mat;
using cv::VideoCapture;

class WorkerThread : public QObject
{
    Q_OBJECT

private:
    QThread thread;
    VideoCapture video;
public:
    WorkerThread();
    ~WorkerThread();

    Mat getFrame();
    Mat getFrame(double _frame);

    double getTotalFrames();
    void loadVideo(QString _path);
};

#endif // VIDEOMANAGEMENT_H
