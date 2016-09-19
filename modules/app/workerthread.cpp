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

QImage WorkerThread::matToQimage(const Mat &_frame)
{
    if (_frame.type() == CV_8UC3)
    {
        const uchar *qImageBuffer = const_cast<uchar*>(_frame.data);
        QImage img(qImageBuffer, _frame.cols, _frame.rows, static_cast<int>(_frame.step), QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qErrnoWarning("ERROR: Mat could not be converted to QImage.");
        return QImage();
    }
}
