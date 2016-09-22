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
    delete(this);
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

QImage VideoManager::matToQimage(const Mat &_frame)
{
    return this->worker->matToQimage(_frame);
}
