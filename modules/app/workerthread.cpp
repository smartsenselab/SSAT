#include "workerthread.h"

WorkerThread::WorkerThread()
{
    this->playing = false;
}

WorkerThread::~WorkerThread()
{
    this->clearVideo();
}

Mat WorkerThread::getFrame()
{
    Mat frame;
    this->video >> frame;
    return frame;
}

Mat WorkerThread::getFrame(double _frameId)
{
    Mat frame;
    this->video.set(CV_CAP_PROP_POS_FRAMES, _frameId);
    this->video >> frame;
    return frame;
}

double WorkerThread::getFrameId()
{
    return this->video.get(CV_CAP_PROP_POS_FRAMES);
}

double WorkerThread::getTotalFrames()
{
    return this->video.get(CV_CAP_PROP_FRAME_COUNT);
}

bool WorkerThread::isPlaying()
{
    return this->playing;
}

void WorkerThread::isPlaying(bool _condition)
{
    this->playing = _condition;
}

void WorkerThread::clearVideo()
{
    this->video.release();
}

void WorkerThread::loadVideo(QString _path)
{
    this->video.open(_path.toStdString());
}

void WorkerThread::playVideo()
{
    while(this->playing)
    {
         Mat frameMat = this->getFrame();
         std::cout << this->getFrameId() << std::endl;
//         const QImage frameQImage = this->matToQimage(frameMat);
//         emit signal_frameToDisplay(frameQImage);
    }
}

QImage WorkerThread::matToQimage(const Mat &_frameId)
{
    if (_frameId.type() == CV_8UC3)
    {
        const uchar *qImageBuffer = const_cast<uchar*>(_frameId.data);
        QImage img(qImageBuffer, _frameId.cols, _frameId.rows, static_cast<int>(_frameId.step), QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qErrnoWarning("ERROR: Mat could not be converted to QImage.");
        return QImage();
    }
}
