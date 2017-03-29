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

    bool addBox(const unsigned int _key, const BoundingBox &_box);
    bool addBox(const unsigned int _key, const Rect &_box);

    BoundingBox getBoxes(const unsigned int _key) const;
    map<unsigned int, BoundingBox> getBoxes() const;

    void setBox(const map<unsigned int, BoundingBox> &_boxes);

    void operator=(const Frame &_frame);

private:
    map<unsigned int, BoundingBox> boxes;
};

#endif // FRAME_H
