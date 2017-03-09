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
    this->setIdentifier(-1);
    this->setInitialFrameId(_iniFrame);
    this->setFinalFrameId(_endFrame);
    this->setCategory(_category);
    this->setLabel(_label);
    this->setInfo(_info);
}

FrameBasedData::FrameBasedData(const int _identifier,
                               const int _iniFrame,
                               const int _endFrame,
                               const string &_category,
                               const string &_label,
                               const string &_info)
{
    this->setIdentifier(_identifier);
    this->setInitialFrameId(_iniFrame);
    this->setFinalFrameId(_endFrame);
    this->setCategory(_category);
    this->setLabel(_label);
    this->setInfo(_info);
}

int FrameBasedData::getIdentifier() const
{
    return this->identifier;
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

void FrameBasedData::setIdentifier(const int _id)
{
    this->identifier = _id;
}

void FrameBasedData::setInitialFrameId(const int _ini)
{
    this->initialFrameId = _ini;
}

void FrameBasedData::setFinalFrameId(const int _end)
{
    this->finalFrameId = _end;
}

void FrameBasedData::setCategory(const string &_category)
{
    this->category = _category;
}

void FrameBasedData::setLabel(const string &_label)
{
    this->label = _label;
}

void FrameBasedData::setInfo(const string &_info)
{
    this->info = _info;
}
