#include "data.h"

Data::Data()
{

}

Data::Data(const string &_id, const string &_label)
{
    this->setId(_id);
    this->setLabel(_label);
}

string Data::getId() const
{
    return this->id;
}

string Data::getLabel() const
{
    return this->label;
}

void Data::setId(const string &_id)
{
    this->id = _id;
}

void Data::setLabel(const string &_label)
{
    this->label = _label;
}
