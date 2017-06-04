#ifndef FRAME_H
#define FRAME_H

#include <map>
#include <string>
#include <vector>
using std::map;
using std::pair;
using std::string;
using std::vector;

#include <opencv2/core/core.hpp>
using cv::Rect;

#include "boundingbox.h"

class Frame : public Data
{
public:
    Frame();

    bool addBox(const string &_key, const BoundingBox &_box, string color);
    bool addBox(const string &_key, const Rect &_box, string color);

    BoundingBox getBoxes(const string &_key) const;
    map<string, BoundingBox> getBoxes() const;

    void setBox(const map<string, BoundingBox> &_boxes);

    void operator=(const Frame &_frame);

private:
    map<string, BoundingBox> boxes;
};

#endif // FRAME_H
