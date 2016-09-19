#include "workerthread.h"

WorkerThread::WorkerThread()
{

}

WorkerThread::~WorkerThread()
{

}

Mat WorkerThread::getFrame()
{
    Mat frame;
    this->video >> frame;
    return frame;
}

Mat WorkerThread::getFrame(double _frame)
{
    Mat frame;
    this->video.set(CV_CAP_PROP_POS_FRAMES, _frame);
    this->video >> frame;
    return frame;
}

double WorkerThread::getTotalFrames()
{
    return this->video.get(CV_CAP_PROP_FRAME_COUNT);
}

void WorkerThread::loadVideo(QString _path)
{
    this->video.open(_path.toStdString());
}
