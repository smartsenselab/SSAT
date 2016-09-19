#include "videomanager.h"

VideoManager::VideoManager()
{
    this->worker = new WorkerThread;
    this->worker->moveToThread(&thread);
    this->thread.start();
}

VideoManager::~VideoManager()
{
    this->thread.quit();
    this->thread.wait();
    delete(this->worker);
}

Mat VideoManager::getFrame()
{
    return this->worker->getFrame();
}

Mat VideoManager::getFrame(double _frame)
{
    return this->worker->getFrame(_frame);
}

double VideoManager::getTotalFrames()
{
    return this->worker->getTotalFrames();
}

void VideoManager::loadVideo(QString _path)
{
    this->worker->loadVideo(_path);
}

QImage VideoManager::matToQimage(const Mat &_frame)
{
    return this->worker->matToQimage(_frame);
}
