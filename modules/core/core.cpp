#include <iostream>

#include "core.h"

Core::Core(unsigned int _frames, unsigned int _cores)
{
    this->frames.resize(_frames);
    this->pool = new ThreadPool(_cores);
}

Core::~Core()
{
    delete(this->pool);
}
