#include "core.h"

Core::Core(unsigned int _frames, unsigned int _cores)
{
    this->frames.resize(_frames);
    this->pool = new ThreadPool(_cores);
    this->tagTree = new Attribute("root");
}

Core::~Core()
{
    this->attributes.clear();
    this->frameData.clear();
    this->frames.clear();
    delete(this->pool);
    delete(this->tagTree);
}

Core* Core::getInstance(unsigned int _frames)
{
    unsigned int cores = std::thread::hardware_concurrency() - 1;
    static Core instance(_frames, cores);
    return &instance;
}

Core* Core::getInstance(unsigned int _frames, unsigned int _cores)
{
    static Core instance(_frames, _cores);
    return &instance;
}

void Core::reset(const unsigned int _frames)
{
    this->frameData.clear();
    this->frames.clear();
    this->frames.resize(_frames);
}

void Core::reset(const unsigned int _frames, unsigned int _cores)
{
    this->frameData.clear();
    this->frames.clear();
    this->frames.resize(_frames);

    delete(this->pool);
    this->pool = new ThreadPool(_cores);
}

string Core::getLatestCategory()
{
    return this->latestCategory;
}

string Core::getLatestLabel()
{
    return this->latestLabel;
}

unsigned int Core::getLatestKey()
{
    return this->latestKey;
}

unsigned int Core::getLatestId()
{
    return this->latestId;
}

unsigned int Core::getLargestId()
{
    if(this->tracklets.size() == 0)
    {
        return 0;
    }

    return *(this->tracklets.rbegin());
}

void Core::setLatestCategory(string _category)
{
    this->latestCategory = _category;
}

void Core::setLatestLabel(string _label)
{
    this->latestLabel = _label;
}

void Core::setLatestKey(unsigned int _key)
{
    this->latestKey = _key;
}

void Core::setLatestId(unsigned int _id)
{
    this->latestId = _id;
}

bool Core::setLargestId(unsigned int _id)
{
    if(this->tracklets.find(_id) == this->tracklets.end())
    {
        this->tracklets.insert(_id);
        return true;
    }

    return false;
}

void Core::updateFrameId()
{
    for(unsigned int index = 0; index < this->frames.size(); index++)
    {
        this->frames[index].setId(index);
    }
}
