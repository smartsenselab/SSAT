#include "data.h"

Data::Data()
{ }

Data::Data(const string &_name)
{
    this->setName(_name);
}

Data::Data(const unsigned int &_id, const string &_name)
{
    this->setId(_id);
    this->setName(_name);
}

unsigned int Data::getId() const
{
    return this->id;
}

vector<string> Data::getAttributes(const string &_key) const
{
    vector<string> attributeVector;
    multimap<string, string>::const_iterator it, itlow, itupp;

    if(this->attributes.find(_key) != this->attributes.end())
    {
        itlow = this->attributes.lower_bound(_key);
        itupp = this->attributes.upper_bound(_key);

        for(it = itlow; it != itupp; it++)
        {
            attributeVector.push_back(it->second);
        }
    }

    return attributeVector;
}

vector<string> Data::getComments() const
{
    return this->comments;
}

string Data::getName() const
{
    return this->name;
}

void Data::addAttributes(const string &_key, const string &_attr)
{
    this->attributes.insert(std::make_pair(_key, _attr));
}

void Data::delAttributes(const string &_key)
{
    this->attributes.erase(_key);
}

void Data::delAttributes()
{
    this->attributes.clear();
}

void Data::addComments(const string &_info)
{
    this->comments.push_back(_info);
}

void Data::delComments(const unsigned int _index)
{
    this->comments.erase(this->comments.begin() + _index);
}

void Data::delComments()
{
    this->comments.clear();
}

void Data::setId(const unsigned int &_id)
{
    this->id = _id;
}

void Data::setName(const string &_name)
{
    this->name = _name;
}

void Data::operator=(const Data &_data)
{
    this->attributes = _data.attributes;
    this->id = _data.id;
    this->comments = _data.comments;
    this->name = _data.name;
}
