#include "data.h"

Data::Data()
{

}

Data::Data(const unsigned int &_id, const string &_label)
{
    this->setId(_id);
    this->setName(_label);
}

unsigned int Data::getId() const
{
    return this->id;
}

string Data::getLabels(const unsigned int _index) const
{
    return this->labels.at(_index);
}

vector<string> Data::getLabels() const
{
    return this->labels;
}

string Data::getName() const
{
    return this->name;
}

void Data::setId(const unsigned int &_id)
{
    this->id = _id;
}

void Data::setLabels(const string &_label)
{
    this->labels.push_back(_label);
}

void Data::setName(const string &_name)
{
    this->name = _name;
}

void Data::operator=(const Data &_data)
{
    this->id = _data.id;
    this->labels = _data.labels;
    this->name = _data.name;
}
