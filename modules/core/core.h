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
    static Core *instance;

    ThreadPool *pool;
    vector<Frame> frames;

    Core(unsigned int _frames, unsigned int _cores);
    ~Core();

public:
    static Core* createCore(unsigned int _frames)
    {
        unsigned int cores = std::thread::hardware_concurrency();
        if(!instance)
        {
            instance = new Core(_frames, cores);
        }
        return instance;
    }

    static Core* createCore(unsigned int _frames, unsigned int _cores)
    {
        if(!instance)
        {
            instance = new Core(_frames, _cores);
        }
        return instance;
    }

    static Core* getCore()
    {
        return instance;
    }

public:
    void runTracker(const string  &_videoName, const unsigned int _frameId,
                    const string &_boxName, int identifier, int status);
};
