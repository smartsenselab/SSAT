#include "core.h"

Core::Core(unsigned int _frames, unsigned int _cores)
{
    this->frames.resize(_frames);
    this->pool = new ThreadPool(_cores);

    this->attributes.insert(std::pair<string, string>("Object_recognition", "Table"));
    this->attributes.insert(std::pair<string, string>("Object_recognition", "Tennis"));
    this->attributes.insert(std::pair<string, string>("Object_recognition", "Desk"));
    this->attributes.insert(std::pair<string, string>("Object_recognition", "Television"));

    this->attributes.insert(std::pair<string, string>("Person_identification", "Breno"));
    this->attributes.insert(std::pair<string, string>("Person_identification", "Danilo"));
    this->attributes.insert(std::pair<string, string>("Person_identification", "Davi"));
    this->attributes.insert(std::pair<string, string>("Person_identification", "Rafael"));
}

Core::~Core()
{
    this->attributes.clear();
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
    this->frames.clear();
    this->frames.resize(_frames);
}

void Core::reset(const unsigned int _frames, unsigned int _cores)
{
    this->frames.clear();
    this->frames.resize(_frames);

    delete(this->pool);
    this->pool = new ThreadPool(_cores);
}
