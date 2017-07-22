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
    ///
    /// \brief BoundingBox BoundingBox default constructor
    ///
    BoundingBox();

    ///
    /// \brief BoundingBox BoundingBox constructor
    /// \param _x The X cordinate of the boundingbox
    /// \param _y The Y cordinate of the boundingbox
    /// \param _w The width of the boundingbox
    /// \param _h The height of the boundingbox
    ///
    BoundingBox(const int &_x,
                const int &_y,
                const int &_w,
                const int &_h);

    ///
    /// \brief BoundingBox BoundingBox constructor
    /// \param _category A category for the bounding-box
    /// \param _info An info for the bounding-box
    /// \param _label A label for the bounding-box
    /// \param _name A name for the bounding-box
    /// \param _x The X cordinate of the boundingbox
    /// \param _y The Y cordinate of the boundingbox
    /// \param _w The width of the boundingbox
    /// \param _h The height of the boundingbox
    ///
    BoundingBox(const string &_category,
                const string &_info,
                const string &_label,
                const string &_name,
                const int &_x,
                const int &_y,
                const int &_w,
                const int &_h);

    ///
    /// \brief BoundingBox BoundingBox constructor
    /// \param _id An identifier for the bounding-box
    /// \param _category A category for the bounding-box
    /// \param _info An info for the bounding-box
    /// \param _label A label for the bounding-box
    /// \param _name A name for the bounding-box
    /// \param _x The X cordinate of the boundingbox
    /// \param _y The Y cordinate of the boundingbox
    /// \param _w The width of the boundingbox
    /// \param _h The height of the boundingbox
    ///
    BoundingBox(const unsigned int &_id,
                const string &_category,
                const string &_info,
                const string &_label,
                const string &_name,
                const int &_x,
                const int &_y,
                const int &_w,
                const int &_h);

    ///
    /// \param _id  An identifier for the bounding-box
    /// \param _box A struct holding X,Y,W and H values
    ///
    BoundingBox(const unsigned int _id, const Rect &_box);

    ///
    /// \brief BoundingBox BoundingBox copy constructor
    /// \param _box Another BoundingBox
    ///
    BoundingBox(const BoundingBox &_box);

    ///
    /// \brief getX Get the x cordinate of the boundingbox
    ///
    int getX() const;

    ///
    /// \brief getY Get the y cordinate of the boudingbox
    ///
    int getY() const;

    ///
    /// \brief getW Get the boundingbox Width
    ///
    int getW() const;

    ///
    /// \brief getH Get the boudingbox Heigth
    ///
    int getH() const;

    ///
    /// \brief setX Set the boundingbox's x cordinate
    /// \param _x New value of x
    ///
    void setX(const int _x);

    ///
    /// \brief setY Set the boundingbox's y coordinate
    /// \param _y New value of y
    ///
    void setY(const int _y);

    ///
    /// \brief setW Set the boundingbox width
    /// \param _w New value of width
    ///
    void setW(const int _w);

    ///
    /// \brief setH Set the boundingbox heigth
    /// \param _h New value of heigth
    ///
    void setH(const int _h);

    ///
    /// \brief operator = Update boundingbox values(attributes, cordinates, comments, id, name)
    /// \param _box Updated BoudingBox values
    ///
    void operator=(const BoundingBox &_box);


private:
    Rect coordinates; //boundingbox coordinates(x, y, width, heigth)
};

#endif // BOUNDINGBOX_H
