#include "frame.h"

Frame::Frame()
{
}

bool Frame::addBox(const unsigned int _key, const BoundingBox &_box)
{
    if(this->boxes.find(_key) == this->boxes.end())
    {
        this->boxes.insert(pair<unsigned int, BoundingBox>(_key, _box));
        return true;
    }

    return false;
}

bool Frame::addBox(const unsigned int _key, const Rect &_box)
{
    if(this->boxes.find(_key) == this->boxes.end())
    {
        BoundingBox bbox(_key, _box);
        this->boxes.insert(pair<unsigned int, BoundingBox>(_key, bbox));

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

BoundingBox Frame::getBoxes(const unsigned int _key) const
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

void Frame::operator=(const Frame &_frame)
{    
    this->id = _frame.id;
    this->category = _frame.category;
    this->info = _frame.info;
    this->label = _frame.label;
    this->name = _frame.name;

    this->boxes = _frame.boxes;
}
