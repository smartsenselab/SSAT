#include "videomanager.h"

VideoManager::VideoManager()
{
    this->worker = new WorkerThread;
    this->worker->moveToThread(&thread);
    this->thread.start();
}

VideoManager::~VideoManager()
{
    this->worker->clearVideo();
    this->thread.quit();
    this->thread.wait();
    delete(this->worker);
}

Mat VideoManager::getFrame()
{
    return this->worker->getFrame();
}

Mat VideoManager::getFrame(double _frameId)
{
    return this->worker->getFrame(_frameId);
}

double VideoManager::getFrameId()
{
    return this->worker->getFrameId();
}

double VideoManager::getTotalFrames()
{
    return this->worker->getTotalFrames();
}

double VideoManager::getVideoFPS()
{
    return this->worker->getVideoFPS();
}

double VideoManager::getPercentage(){
    return this->worker->getFrameId() / this->worker->getTotalFrames();
}

int VideoManager::getTime(){
    return static_cast<int>((this->worker->getTotalFrames() / this->worker->getVideoFPS()) * this->getPercentage());
}

bool VideoManager::isPlaying()
{
    return this->worker->isPlaying();
}

void VideoManager::isPlaying(bool _condition)
{
    this->worker->isPlaying(_condition);
}

void VideoManager::clearVideo()
{
    this->worker->clearVideo();
}

void VideoManager::loadVideo(QString _path)
{
    this->worker->loadVideo(_path);
}

void VideoManager::exportJSON(Core &_singleton, const QString &_jsonName)
{
    this->worker->exportJSON(_singleton, _jsonName);
}

void VideoManager::importJSON(Core &_singleton, QFrameBasedTableModel *_tableModel, const QString &_jsonName)
{
    this->worker->importJSON(_singleton, _tableModel, _jsonName);
}

QImage VideoManager::matToQimage(const Mat &_frame)
{
    return this->worker->matToQimage(_frame);
}

void VideoManager::insertFrameBasedSegment(Core &_singleton, const FrameBasedData &_data)
{
    this->worker->insertFrameBasedSegment(_singleton, _data);
}

void VideoManager::alterFrameBasedSegment(Core &_singleton, const FrameBasedData &_data, const int _index)
{
    this->worker->alterFrameBasedSegment(_singleton, _data, _index);
}

void VideoManager::exponentialForget(Core &_singleton, const BoundingBox _focusBox, const unsigned int _frameId, const unsigned int _numFrames)
{
    this->worker->exponentialForget(_singleton, _focusBox, _frameId, _numFrames);
}

void VideoManager::replicateBoundingBoxFromCore(Core &_singleton, const unsigned int _bboxKey, const unsigned int _numFrames)
{
    this->worker->replicateBoundingBoxFromCore(_singleton, _bboxKey, _numFrames);
}

void VideoManager::removeBoxSequenceFromCore(Core &_singleton, const unsigned int _bboxKey)
{
    this->worker->removeBoxSequenceFromCore(_singleton, _bboxKey);
}
