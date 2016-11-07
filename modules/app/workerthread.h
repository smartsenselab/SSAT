#ifndef VIDEOMANAGEMENT_H
#define VIDEOMANAGEMENT_H

#include <QImage>
#include <QObject>
#include <QThread>
#include <QFile>
#include<QJsonArray>
#include<QJsonDocument>
#include <QJsonObject>
#include <QDate>

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::Mat;
using cv::VideoCapture;

#include "core.h"
#include "framebaseddata.h"

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

    void slot_exportJson(Core &_singleton,QString jsonName);
    void importJSON(Core &_core, const QString &_path);

    QImage matToQimage(const Mat &_frame);

    void allotFrameBasedSegment(Core &_singleton, const FrameBasedData &_data);
};

#endif // VIDEOMANAGEMENT_H
