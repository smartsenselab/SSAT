#include "data.h"

Data::Data()
{
    this->setId(0);
    this->setKey(0);
}

Data::Data(const unsigned int &_id)
{
    this->setId(_id);
    this->setKey(0);

    this->setCategory("");
    this->setInfo("");
    this->setLabel("");
    this->setName("");
}

Data::Data(const unsigned int &_id, const unsigned int &_key)
{
    this->setId(_id);
    this->setKey(_key);

    this->setCategory("");
    this->setInfo("");
    this->setLabel("");
    this->setName("");
}


Data::Data(const string &_category,
           const string &_info,
           const string &_label,
           const string &_name)
{
    this->setId(0);
    this->setKey(0);

    this->setCategory(_category);
    this->setInfo(_info);
    this->setLabel(_label);
    this->setName(_name);
}

Data::Data(const unsigned int &_id,
           const string &_category,
           const string &_info,
           const string &_label,
           const string &_name)
{
    this->setId(_id);
    this->setKey(0);

    this->setCategory(_category);
    this->setInfo(_info);
    this->setLabel(_label);
    this->setName(_name);
}

Data::Data(const unsigned int &_id,
           const unsigned int &_key,
           const string &_category,
           const string &_info,
           const string &_label,
           const string &_name)
{
    this->setId(_id);
    this->setKey(_key);

    this->setCategory(_category);
    this->setInfo(_info);
    this->setLabel(_label);
    this->setName(_name);
}

unsigned int Data::getId() const
{
    return this->id;
}

unsigned int Data::getKey() const
{
    return this->key;
}

string Data::getCategory() const
{
    return this->category;
}

string Data::getInfo() const
{
    return this->info;
}

string Data::getLabel() const
{
    return this->label;
}

string Data::getName() const
{
    return this->name;
}

void Data::setId(const unsigned int &_id)
{
    this->id = _id;
}

void Data::setKey(const unsigned int &_key)
{
    this->key = _key;
}

void Data::setCategory(const string &_category)
{
    this->category = _category;
}

void Data::setInfo(const string &_info)
{
    this->info = _info;
}

void Data::setLabel(const string &_label)
{
    this->label = _label;
}

void Data::setName(const string &_name)
{
    this->name = _name;
}

void Data::operator=(const Data &_data)
{
    this->id = _data.id;
    this->key = _data.key;
    this->category = _data.category;
    this->info = _data.info;
    this->label = _data.label;
    this->name = _data.name;
}
