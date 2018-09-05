#include "qvideomanager.h"

QVideoManager::QVideoManager()
{
    this->worker = new QWorkerThread;
    this->worker->moveToThread(&thread);
    this->thread.start();
}

QVideoManager::~QVideoManager()
{
    this->worker->clearVideo();
    this->thread.quit();
    this->thread.wait();
    delete(this->worker);
}

Mat QVideoManager::getFrame()
{
    return this->worker->getFrame();
}

Mat QVideoManager::getFrame(double _frameId)
{
    return this->worker->getFrame(_frameId);
}

double QVideoManager::getFrameId()
{
    return this->worker->getFrameId();
}

double QVideoManager::getTotalFrames()
{
    return this->worker->getTotalFrames();
}

double QVideoManager::getVideoFPS()
{
    return this->worker->getVideoFPS();
}

double QVideoManager::getPercentage(){
    return this->worker->getFrameId() / this->worker->getTotalFrames();
}

int QVideoManager::getTime(){
    return static_cast<int>((this->worker->getTotalFrames() / this->worker->getVideoFPS()) * this->getPercentage());
}

bool QVideoManager::isPlaying()
{
    return this->worker->isPlaying();
}

void QVideoManager::isPlaying(bool _condition)
{
    this->worker->isPlaying(_condition);
}

void QVideoManager::clearVideo()
{
    this->worker->clearVideo();
}

void QVideoManager::loadVideo(QString _path)
{
    this->worker->loadVideo(_path);
}

void QVideoManager::exportJSON(Core &_singleton, const QString &_jsonName)
{
    this->worker->exportJSON(_singleton, _jsonName);
}

void QVideoManager::importJSON(Core &_singleton, QFrameBasedTableModel *_tableModel, const QString &_jsonName)
{
    this->worker->importJSON(_singleton, _tableModel, _jsonName);
}

QImage QVideoManager::matToQimage(const Mat &_frame)
{
    return this->worker->matToQimage(_frame);
}

void QVideoManager::insertFrameBasedSegment(Core &_singleton, const FrameBasedData &_data)
{
    this->worker->insertFrameBasedSegment(_singleton, _data);
}

void QVideoManager::alterFrameBasedSegment(Core &_singleton, const FrameBasedData &_data, const int _index)
{
    this->worker->alterFrameBasedSegment(_singleton, _data, _index);
}

void QVideoManager::exponentialForget(Core &_singleton, const BoundingBox _focusBox, const unsigned int _frameId, const unsigned int _numFrames)
{
    this->worker->exponentialForget(_singleton, _focusBox, _frameId, _numFrames);
}

void QVideoManager::replicateBoundingBoxFromCore(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames)
{
    this->worker->replicateBoundingBoxFromCore(_singleton, _bboxKey, _numFrames);
}

void QVideoManager::replicateBoundingBoxFromCoreBackwards(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames)
{
    this->worker->replicateBoundingBoxFromCoreBackwards(_singleton, _bboxKey, _numFrames);
}

void QVideoManager::removeBoxSequenceFromCore(Core &_singleton, const unsigned int _bboxKey)
{
    this->worker->removeBoxSequenceFromCore(_singleton, _bboxKey);
}
