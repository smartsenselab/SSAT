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

void VideoManager::exportJSON(const Core &_core)
{
    this->worker->exportJSON(_core);
}

void VideoManager::importJSON(Core &_core, const QString &_path)
{
    this->worker->importJSON(_core, _path);
}

QImage VideoManager::matToQimage(const Mat &_frame)
{
    return this->worker->matToQimage(_frame);
}

void VideoManager::allotFrameBasedSegment(Core &_singleton, const FrameBasedData &_data)
{
    this->worker->allotFrameBasedSegment(_singleton, _data);
}
