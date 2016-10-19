#include "framebaseddata.h"

FrameBasedData::FrameBasedData()
{
    this->setInitialFrameId(0);
    this->setFinalFrameId(0);
}

FrameBasedData::FrameBasedData(const unsigned int _iniFrame,
               const unsigned int _endFrame,
               const string &_category,
               const string &_label,
               const string &_name)
{
    this->setInitialFrameId(_iniFrame);
    this->setFinalFrameId(_endFrame);
    this->setCategory(_category);
    this->setLabel(_label);
    this->setName(_name);
}

unsigned int FrameBasedData::getInitialFrameId() const
{
    return this->initialFrameId;
}

unsigned int FrameBasedData::getFinalFrameId() const
{
    return this->finalFrameId;
}

string FrameBasedData::getCategory() const
{
    return this->category;
}

string FrameBasedData::getLabel() const
{
    return this->label;
}

string FrameBasedData::getName() const
{
    return this->name;
}

void FrameBasedData::setInitialFrameId(const unsigned int _id)
{
    this->initialFrameId = _id;
}

void FrameBasedData::setFinalFrameId(const unsigned int _id)
{
    this->finalFrameId = _id;
}

void FrameBasedData::setCategory(const string &_category)
{
    this->category = _category;
}

void FrameBasedData::setLabel(const string &_label)
{
    this->label = _label;
}

void FrameBasedData::setName(const string &_name)
{
    this->name = _name;
}
