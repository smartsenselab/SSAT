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
    Frame(const unsigned int &_id);

    Frame(const unsigned int &_id,
          const string &_category,
          const string &_info,
          const string &_label,
          const string &_name);

    Frame(const unsigned int &_id,
          const unsigned int &_key,
          const string &_category,
          const string &_info,
          const string &_label,
          const string &_name);

    bool addBox(const BoundingBox &_box);
    bool addBox(const Rect &_box);
    bool remBox(const unsigned int &_key);
    unsigned int getLargestKey();

    BoundingBox getBox(const unsigned int _key) const;
    map<unsigned int, BoundingBox> getBoxes() const;

    void setBox(const map<unsigned int, BoundingBox> &_boxes);
    void setBox(const unsigned int _key, const Rect &_box);

    void operator=(const Frame &_frame);

private:
    map<unsigned int, BoundingBox> boxes;
};

#endif // FRAME_H
