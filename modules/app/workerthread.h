#ifndef VIDEOMANAGEMENT_H
#define VIDEOMANAGEMENT_H

#include <QImage>
#include <QObject>
#include <QThread>

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::Mat;
using cv::VideoCapture;

class WorkerThread : public QObject
{
    Q_OBJECT

private:
    bool playing;
    VideoCapture video;
public:
    WorkerThread();
    ~WorkerThread();

    Mat getFrame();
    Mat getFrame(double _frameId);
    double getFrameId();
    double getTotalFrames();
    double getVideoFPS();

    bool isPlaying();
    void isPlaying(bool _condition);

    void clearVideo();
    void loadVideo(QString _path);
    void playVideo();
    QImage matToQimage(const Mat &_frame);
};

#endif // VIDEOMANAGEMENT_H
