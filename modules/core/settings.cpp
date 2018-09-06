#include "settings.h"

Settings::Settings()
{
    this->setCurrentSeparator(".");
    this->setFrameSkip(50);
    this->setLargestId(0);
    this->setLatestKey(0);
}

string Settings::getCurrentSeparator() const
{
    return this->curretSeparator;
}

string Settings::getLatestCategory() const
{
    return this->latestCategory;
}

string Settings::getLatestLabel() const
{
    return this->latestLabel;
}

unsigned int Settings::getFrameSkip() const
{
    return frameSkip;
}

unsigned int Settings::getLargestId() const
{
    if(this->tracklets.size() == 0)
    {
        return 0;
    }

    return *(this->tracklets.rbegin());
}

unsigned int Settings::getLatestKey() const
{
    return this->latestKey;
}

unsigned int Settings::getLatestId() const
{
    return this->latestId;
}

void Settings::setCurrentSeparator(string _separator)
{
    this->curretSeparator = _separator;
}

void Settings::setLatestCategory(string _category)
{
    this->latestCategory = _category;
}

void Settings::setLatestLabel(string _label)
{
    this->latestLabel = _label;
}

void Settings::setFrameSkip(unsigned int _frameSkip)
{
    frameSkip = _frameSkip;
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

void Settings::setLatestKey(unsigned int _key)
{
    this->latestKey = _key;
}

void Settings::setLatestId(unsigned int _id)
{
    this->latestId = _id;
}
