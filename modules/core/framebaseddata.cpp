#include "framebaseddata.h"

FrameBasedData::FrameBasedData()
{
    this->setInitialFrameId(-1);
    this->setFinalFrameId(-1);
}

FrameBasedData::FrameBasedData(const int _iniFrame,
               const int _endFrame,
               const string &_category,
               const string &_label,
               const string &_info)
{
    this->setInitialFrameId(_iniFrame);
    this->setFinalFrameId(_endFrame);
    this->setCategory(_category);
    this->setLabel(_label);
    this->setinfo(_info);
}

int FrameBasedData::getInitialFrameId() const
{
    return this->initialFrameId;
}

int FrameBasedData::getFinalFrameId() const
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

string FrameBasedData::getInfo() const
{
    return this->info;
}

void FrameBasedData::setInitialFrameId(const int _id)
{
    this->initialFrameId = _id;
}

void FrameBasedData::setFinalFrameId(const int _id)
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

void FrameBasedData::setinfo(const string &_info)
{
    this->info = _info;
}
