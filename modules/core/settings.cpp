#include "settings.h"

Settings::Settings()
{
    this->latestId = 0;
    this->latestKey = 0;
}

string Settings::getLatestCategory()
{
    return this->latestCategory;
}

string Settings::getLatestLabel()
{
    return this->latestLabel;
}

unsigned int Settings::getLatestKey()
{
    return this->latestKey;
}

unsigned int Settings::getLatestId()
{
    return this->latestId;
}

void Settings::setLatestCategory(string _category)
{
    this->latestCategory = _category;
}

void Settings::setLatestLabel(string _label)
{
    this->latestLabel = _label;
}

void Settings::setLatestKey(unsigned int _key)
{
    this->latestKey = _key;
}

void Settings::setLatestId(unsigned int _id)
{
    this->latestId = _id;
}
