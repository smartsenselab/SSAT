#ifndef VIDEOMANAGEMENT_H
#define VIDEOMANAGEMENT_H

#include <QtCore>

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

    void exportJSON(Core &_singleton, const QString &_jsonName);
    void importJSON(Core &_singleton, const QString &_jsonName);

    QImage matToQimage(const Mat &_frame);

    void insertFrameBasedSegment(Core &_singleton, const FrameBasedData &_data);
    void alterFrameBasedSegment(Core &_singleton, const FrameBasedData &_data, const int _index);
};

#endif // VIDEOMANAGEMENT_H
