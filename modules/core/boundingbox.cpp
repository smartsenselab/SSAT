#include "boundingbox.h"

BoundingBox::BoundingBox() :
    Data()
{
    this->setX(-1);
    this->setY(-1);
    this->setW(-1);
    this->setH(-1);
    this->toModify = true;
}

BoundingBox::BoundingBox(const int &_x,
                         const int &_y,
                         const int &_w,
                         const int &_h,
                         const bool _mod) :
    Data()
{
    this->setX(_x);
    this->setY(_y);
    this->setW(_w);
    this->setH(_h);
    this->toModify = _mod;
}

BoundingBox::BoundingBox(const unsigned int &_id,
                         const string &_category,
                         const string &_info,
                         const string &_label,
                         const string &_name,
                         const int &_x,
                         const int &_y,
                         const int &_w,
                         const int &_h,
                         const bool _mod) :
    Data(_id, _category, _info, _label, _name)
{
    this->setX(_x);
    this->setY(_y);
    this->setW(_w);
    this->setH(_h);
    this->toModify = _mod;
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
                         const int &_h,
                         const bool _mod) :
    Data(_id, _key, _category, _info, _label, _name)
{
    this->setX(_x);
    this->setY(_y);
    this->setW(_w);
    this->setH(_h);
    this->toModify = _mod;
}

BoundingBox::BoundingBox(const unsigned int &_id, const unsigned int &_key, const Rect &_coordinates, const bool _mod)
{
    this->coordinates = _coordinates;
    this->setId(_id);
    this->setKey(_key);
    this->toModify = _mod;
}

BoundingBox::BoundingBox(const unsigned int &_key, const Rect &_coordinates, const bool _mod)
{
    this->coordinates = _coordinates;
    this->setKey(_key);
    this->toModify = _mod;
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

int BoundingBox::getModify() const
{
    return this->toModify;
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

void BoundingBox::setModify(const bool _mod)
{
    this->toModify = _mod;
}

void BoundingBox::setCoordinates(const int _x, const int _y, const int _w, const int _h)
{
    this->setX(_x);
    this->setY(_y);
    this->setW(_w);
    this->setH(_h);
}

bool BoundingBox::isValid()
{
    if ((this->getX() > 0) && (this->getY() > 0) && (this->getW() > 0) && (this->getH() > 0))
    {
        return true;
    }

    return false;
}

void BoundingBox::operator=(const BoundingBox &_box)
{
    this->id = _box.id;
    this->key = _box.key;
    this->category = _box.category;
    this->info = _box.info;
    this->label = _box.label;
    this->name = _box.name;
    this->toModify = _box.toModify;

    this->coordinates = _box.coordinates;
}
