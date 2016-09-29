#ifndef CORE_H
#define CORE_H

#include <thread>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
using cv::Rect;
using cv::VideoCapture;

#include "frame.h"
#include "threadpool.h"

/*
 *  Design Pattern: SINGLETON
 */

class Core {
private:
    ThreadPool *pool;
    vector<Frame> frames;

    Core(unsigned int _frames, unsigned int _cores);
    ~Core();

public:
    static Core* getInstance(unsigned int _frames);
    static Core* getInstance(unsigned int _frames, unsigned int _cores);

    void runTracker(const string  &_videoName, const unsigned int _frameId,
                    const string &_boxName, int identifier, int status);
};


#endif // CORE_H
