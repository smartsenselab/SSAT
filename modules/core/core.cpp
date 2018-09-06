#include "core.h"

Core::Core(unsigned int _frames, unsigned int _cores)
{
    this->frames.resize(_frames);
    this->pool = new ThreadPool(_cores);
    this->labelTree = new Attribute();
}

Core::~Core()
{
    this->attributes.clear();
    this->frameData.clear();
    this->frames.clear();
    delete(this->pool);
    delete(this->labelTree);
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
    // this->tagTree->clear();
}

void Core::reset(const unsigned int _frames, unsigned int _cores)
{
    this->frameData.clear();
    this->frames.clear();
    this->frames.resize(_frames);
    // this->tagTree->clear();

    delete(this->pool);
    this->pool = new ThreadPool(_cores);
}

void Core::updateFrameId()
{
    for(unsigned int index = 0; index < this->frames.size(); index++)
    {
        this->frames[index].setId(index);
    }
}
