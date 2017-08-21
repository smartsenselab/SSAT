#include "core.h"

Core::Core(unsigned int _frames, unsigned int _cores)
{
    this->frames.resize(_frames);
    this->pool = new ThreadPool(_cores);
}

Core::~Core()
{
    this->attributes.clear();
    this->frameData.clear();
    this->frames.clear();
    delete(this->pool);
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

void Core::exponentialForget(const BoundingBox _focusBox, const unsigned int _frameId, const unsigned int _numFrames)
{
    double holder = 1.0;
    double step = 1.0 / _numFrames;
    int newX, newY, newW, newH;

    for(unsigned int frameIndex = _frameId;
        frameIndex < this->frames.size() && frameIndex <= _frameId + _numFrames;
        frameIndex++)
    {
        map<unsigned int, BoundingBox> currentBoxes = this->frames[frameIndex].getBoxes();
        map<unsigned int, BoundingBox>::iterator it = currentBoxes.find(_focusBox.getId());
        if(it != currentBoxes.end())
        {
            newX = (holder * _focusBox.getX()) + ((1 - holder) * it->second.getX());
            newY = (holder * _focusBox.getY()) + ((1 - holder) * it->second.getY());
            newW = (holder * _focusBox.getW()) + ((1 - holder) * it->second.getW());
            newH = (holder * _focusBox.getH()) + ((1 - holder) * it->second.getH());

            std::cout << newX << ":"<< newY << ":" << newW << ":"<< newH << std::endl;

            it->second.setCoordinates(newX, newY, newW, newH);
            holder -= step;
        }
        else
        {
            break;
        }
    }
}

void Core::updateFrameId()
{
    for(unsigned int index = 0; index < this->frames.size(); index++)
    {
        this->frames[index].setId(index);
    }
}
