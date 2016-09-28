#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <map>
#include <string>
#include <vector>
using std::map;
using std::string;
using std::vector;

#include <opencv2/core/core.hpp>
using cv::Rect;

#include "data.h"

class BoundingBox : public Data
{
public:
    BoundingBox();
    BoundingBox(const BoundingBox &_box);
    BoundingBox(const Rect &_box);
    BoundingBox(const int _x, const int _y,
                const int _w, const int _h);

    int getX();
    int getY();
    int getW();
    int getH();

    void setX(const int _x);
    void setY(const int _y);
    void setW(const int _w);
    void setH(const int _h);

    void operator=(const BoundingBox &_box);

private:
    Rect coordinates;
};

#endif // BOUNDINGBOX_H
