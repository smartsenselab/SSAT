#ifndef VIDEOMANAGEMENT_H
#define VIDEOMANAGEMENT_H

#include <QtCore>

#include <QDate>
#include <QFile>
#include <QImage>
#include <QObject>
#include <QTableView>
#include <QThread>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::Mat;
using cv::VideoCapture;

#include "core.h"
#include "framebaseddata.h"
#include "qframebasedtablemodel.h"

class QWorkerThread : public QObject
{
    Q_OBJECT

private:
    bool playing;
    VideoCapture video;

public:
    QWorkerThread();
    ~QWorkerThread();

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
    void importJSON(Core &_singleton, QFrameBasedTableModel *_tableModel, const QString &_jsonName);

    QImage matToQimage(const Mat &_frame);

    void insertFrameBasedSegment(Core &_singleton, const FrameBasedData &_data);
    void alterFrameBasedSegment(Core &_singleton, const FrameBasedData &_data, const int _index);
    void exponentialForget(Core &_singleton, BoundingBox _focusBox, const unsigned int _frameId, const unsigned int _numFrames);
    void replicateBoundingBoxFromCore(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames);
    void replicateBoundingBoxFromCoreBackwards(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames);
    void removeBoxSequenceFromCore(Core &_singleton, const unsigned int _bboxKey);
};

#endif // VIDEOMANAGEMENT_H
