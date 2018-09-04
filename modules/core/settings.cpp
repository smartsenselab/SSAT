#include "settings.h"

Settings::Settings()
{
    this->latestId = 0;
    this->latestKey = 0;
}

unsigned int Settings::getLargestId()
{
    if(this->tracklets.size() == 0)
    {
        return 0;
    }

    return *(this->tracklets.rbegin());
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

bool Settings::setLargestId(unsigned int _id)
{
    if(this->tracklets.find(_id) == this->tracklets.end())
    {
        this->tracklets.insert(_id);
        return true;
    }

    return false;
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
