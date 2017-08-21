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

    unsigned int addBox(const BoundingBox &_box);
    unsigned int addBox(const Rect &_box);
    unsigned int addBox(const unsigned int _id, const BoundingBox &_box);
    unsigned int addBox(const unsigned int _id, const Rect &_box);
    unsigned int getLargestKey();

    BoundingBox getBoxById(const unsigned int _id) const;
    BoundingBox getBoxByKey(const unsigned int _key) const;
    map<unsigned int, BoundingBox> getBoxes() const;
    map<unsigned int, unsigned int> countIdOccurence() const;

    void setBox(const map<unsigned int, BoundingBox> &_boxes);
    void setBox(const unsigned int _key, const Rect &_box);
    void setBox(const unsigned int _key, const BoundingBox &_bbox);
    void setBox(const unsigned int _key, const int _x, const int _y, const int _w, const int _h);

    bool removeBoxById(const unsigned int &_id);
    bool removeBoxByKey(const unsigned int &_key);

    void operator=(const Frame &_frame);

private:
    map<unsigned int, BoundingBox> boxes;
};

#endif // FRAME_H
