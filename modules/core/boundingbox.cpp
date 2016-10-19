#include "boundingbox.h"

BoundingBox::BoundingBox()
{
    this->coordinates.x = -1;
    this->coordinates.y = -1;
    this->coordinates.width = -1;
    this->coordinates.height = -1;
}

BoundingBox::BoundingBox(const BoundingBox &_box)
{
    (*this) = _box;
}

BoundingBox::BoundingBox(const Rect &_coordinates)
{
    this->coordinates = _coordinates;
}

BoundingBox::BoundingBox(const int _x, const int _y,
                         const int _w, const int _h)
{
    this->setX(_x);
    this->setY(_y);
    this->setW(_w);
    this->setH(_h);
}

int BoundingBox::getX() const
{
    return this->coordinates.x;
}

int BoundingBox::getY() const
{
    return this->coordinates.y;
}

int BoundingBox::getW() const
{
    return this->coordinates.width;
}

int BoundingBox::getH() const
{
    return this->coordinates.height;
}

void BoundingBox::setX(const int _x)
{
    if(_x >= 0)
    {
        this->coordinates.x = _x;
    }
}

void BoundingBox::setY(const int _y)
{
    if(_y >= 0)
    {
        this->coordinates.y = _y;
    }
}

void BoundingBox::setW(const int _w)
{
    if(_w >= 0)
    {
        this->coordinates.width = _w;
    }
}

void BoundingBox::setH(const int _h)
{
    if(_h >= 0)
    {
        this->coordinates.height = _h;
    }
}

void BoundingBox::operator=(const BoundingBox &_box)
{
    this->coordinates = _box.coordinates;

    this->attributes = _box.attributes;
    this->comments = _box.comments;
    this->id = _box.id;
    this->name = _box.name;
}
