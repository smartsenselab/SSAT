#include "frame.h"

Frame::Frame()
{
}

bool Frame::addBox(const string &_key, const BoundingBox &_box, string &color)
{
    if(this->boxes.find(_key) == this->boxes.end())
    {
        this->boxes.insert(pair<string, BoundingBox>(_key, _box));
        return true;
    }

    return false;
}

bool Frame::addBox(const string &_key, const Rect &_box, string &color)
{
    if(this->boxes.find(_key) == this->boxes.end())
    {
        BoundingBox bbox(_box, color);
        this->boxes.insert(pair<string, BoundingBox>(_key, bbox));

        return true;
    }

    return false;
}

BoundingBox Frame::getBoxes(const string &_key) const
{
    if(this->boxes.find(_key) != this->boxes.end())
    {
        return this->boxes.at(_key);
    }

    return BoundingBox();
}

map<string, BoundingBox> Frame::getBoxes() const
{
    return this->boxes;
}

void Frame::setBox(const map<string, BoundingBox> &_boxes)
{
    this->boxes = _boxes;
}

void Frame::operator=(const Frame &_frame)
{
    this->boxes = _frame.boxes;

    this->attributes = _frame.attributes;
    this->comments = _frame.comments;
    this->id = _frame.id;
    this->name = _frame.name;
}
