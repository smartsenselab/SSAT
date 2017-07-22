#include "framebaseddata.h"

FrameBasedData::FrameBasedData() :
    Data()
{

}

FrameBasedData::FrameBasedData(const unsigned int &_id) :
    Data(_id)
{

}

FrameBasedData::FrameBasedData(const string &_category,
                               const string &_info,
                               const string &_label,
                               const string &_name,
                               const unsigned int &_ini = 0,
                               const unsigned int &_end = 0) :
    Data(_category, _info, _label, _name)
{
    this->setInitialFrameId(_ini);
    this->setFinalFrameId(_end);
}

FrameBasedData::FrameBasedData(const unsigned int &_id,
                               const string &_category,
                               const string &_info,
                               const string &_label,
                               const string &_name,
                               const unsigned int &_ini = 0,
                               const unsigned int &_end = 0) :
    Data(_id, _category, _info, _label, _name)
{
    this->setInitialFrameId(_ini);
    this->setFinalFrameId(_end);
}

unsigned int FrameBasedData::getInitialFrameId() const
{
    return this->initialFrameId;
}

unsigned int FrameBasedData::getFinalFrameId() const
{
    return this->finalFrameId;
}

void FrameBasedData::setInitialFrameId(const unsigned int _ini)
{
    this->initialFrameId = _ini;
}

void FrameBasedData::setFinalFrameId(const unsigned int _end)
{
    this->finalFrameId = _end;
}

void FrameBasedData::operator=(const FrameBasedData &_frameBasedData)
{
    this->id = _frameBasedData.id;
    this->category = _frameBasedData.category;
    this->info = _frameBasedData.info;
    this->label = _frameBasedData.label;
    this->name = _frameBasedData.name;

    this->initialFrameId = _frameBasedData.initialFrameId;
    this->finalFrameId = _frameBasedData.finalFrameId;
}

