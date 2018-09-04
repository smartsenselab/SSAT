#ifndef CORE_H
#define CORE_H

#include <set>
#include <string>
#include <vector>
using std::set;
using std::string;
using std::vector;

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
using cv::Rect;
using cv::VideoCapture;

#include "attribute.h"
#include "boundingbox.h"
#include "frame.h"
#include "framebaseddata.h"
#include "settings.h"
#include "threadpool.h"

/*
 *  Design Pattern: SINGLETON
 */

class Core
{
private:
    string latestCategory;
    string latestLabel;
    unsigned int latestId;
    unsigned int latestKey;

public:
    Attribute *tagTree;
    Settings setup;
    ThreadPool *pool;
    multimap<string, string> attributes;
    vector<FrameBasedData> frameData;
    vector<Frame> frames;

private:
    Core(unsigned int _frames, unsigned int _cores);
    ~Core();

public:
    static Core* getInstance(unsigned int _frames);
    static Core* getInstance(unsigned int _frames, unsigned int _cores);

    void reset(const unsigned int _frames);
    void reset(const unsigned int _frames, unsigned int _cores);
    void runTracker(const string  &_videoName, const unsigned int _frameId,
                    const string &_boxName, int identifier, int status);

    vector<string> getTagTreeNames();
    void updateFrameId();

private:
    void tagTreeToString(Attribute* _nodeAtt, vector<string> &_nodeNames);
};

#endif // CORE_H
