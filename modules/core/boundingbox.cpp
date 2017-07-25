#include "boundingbox.h"

BoundingBox::BoundingBox() :
    Data()
{
    this->setX(-1);
    this->setY(-1);
    this->setW(0);
    this->setH(0);
}

BoundingBox::BoundingBox(const int &_x,
                         const int &_y,
                         const int &_w,
                         const int &_h) :
    Data()
{
    this->setX(_x);
    this->setY(_y);
    this->setW(_w);
    this->setH(_h);
}

BoundingBox::BoundingBox(const unsigned int &_id,
                         const string &_category,
                         const string &_info,
                         const string &_label,
                         const string &_name,
                         const int &_x,
                         const int &_y,
                         const int &_w,
                         const int &_h) :
    Data(_id, _category, _info, _label, _name)
{
    this->setX(_x);
    this->setY(_y);
    this->setW(_w);
    this->setH(_h);
}

BoundingBox::BoundingBox(const unsigned int &_id,
                         const unsigned int &_key,
                         const string &_category,
                         const string &_info,
                         const string &_label,
                         const string &_name,
                         const int &_x,
                         const int &_y,
                         const int &_w,
                         const int &_h) :
    Data(_id, _key, _category, _info, _label, _name)
{
    this->setX(_x);
    this->setY(_y);
    this->setW(_w);
    this->setH(_h);
}

BoundingBox::BoundingBox(const unsigned int _key, const Rect &_coordinates)
{
    this->setKey(_key);
    this->coordinates = _coordinates;
}

BoundingBox::BoundingBox(const BoundingBox &_box)
{
    (*this) = _box;
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
    this->id = _box.id;
    this->key = _box.key;
    this->category = _box.category;
    this->info = _box.info;
    this->label = _box.label;
    this->name = _box.name;

    this->coordinates = _box.coordinates;
}
