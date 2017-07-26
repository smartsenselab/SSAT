#include "frame.h"

Frame::Frame() :
    Data()
{

}

Frame::Frame(const unsigned int &_id) :
    Data(_id)
{

}

Frame::Frame(const unsigned int &_id,
             const string &_category,
             const string &_info,
             const string &_label,
             const string &_name) :
    Data(_id, _category, _info, _label, _name)
{

}

Frame::Frame(const unsigned int &_id,
             const unsigned int &_key,
             const string &_category,
             const string &_info,
             const string &_label,
             const string &_name) :
    Data(_id, _key, _category, _info, _label, _name)
{

}

unsigned int Frame::addBox(const BoundingBox &_box)
{
    unsigned int key = this->getLargestKey() + 1;
    if(this->boxes.find(key) == this->boxes.end())
    {
        BoundingBox bbox(_box);
        bbox.setKey(key);

        this->boxes.insert(pair<unsigned int, BoundingBox>(key, bbox));
        return key;
    }

    return 0;
}

unsigned int Frame::addBox(const Rect &_box)
{
    unsigned int key = this->getLargestKey() + 1;
    if(this->boxes.find(key) == this->boxes.end())
    {
        BoundingBox bbox(key, _box);
        this->boxes.insert(pair<unsigned int, BoundingBox>(key, bbox));
        return key;
    }

    return 0;
}

bool Frame::remBox(const unsigned int &_key)
{
    if(this->boxes.find(_key) != this->boxes.end())
    {
        this->boxes.erase(_key);
        return true;
    }

    return false;
}

unsigned int Frame::getLargestKey()
{
    if(this->boxes.size() == 0)
    {
        return 0;
    }

    return this->boxes.rbegin()->first;
}

BoundingBox Frame::getBox(const unsigned int _key) const
{
    if(this->boxes.find(_key) != this->boxes.end())
    {
        return this->boxes.at(_key);
    }

    return BoundingBox();
}

map<unsigned int, BoundingBox> Frame::getBoxes() const
{
    return this->boxes;
}

void Frame::setBox(const map<unsigned int, BoundingBox> &_boxes)
{
    this->boxes = _boxes;
}

void Frame::setBox(const unsigned int _key, const Rect &_box)
{
    this->boxes.at(_key).setX(_box.x);
    this->boxes.at(_key).setY(_box.y);
    this->boxes.at(_key).setW(_box.width);
    this->boxes.at(_key).setH(_box.height);
}

void Frame::setBox(const unsigned int _key, const BoundingBox &_bbox)
{
    this->boxes.at(_key) = _bbox;
//    this->boxes.at(_key).setX(_bbox.getX());
//    this->boxes.at(_key).setY(_bbox.getY());
//    this->boxes.at(_key).setW(_bbox.getW());
//    this->boxes.at(_key).setH(_bbox.getH());
}

void Frame::operator=(const Frame &_frame)
{    
    this->id = _frame.id;
    this->key = _frame.key;
    this->category = _frame.category;
    this->info = _frame.info;
    this->label = _frame.label;
    this->name = _frame.name;

    this->boxes = _frame.boxes;
}
