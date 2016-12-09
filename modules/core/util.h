#ifndef UTIL_H
#define UTIL_H

#include <cstring>

#include "framebaseddata.h"

bool sortByIniFrame(FrameBasedData i,FrameBasedData j);
bool sortByEndFrame(FrameBasedData i,FrameBasedData j);
bool sortByName(FrameBasedData i,FrameBasedData j);
bool sortByCategory(FrameBasedData i,FrameBasedData j);
bool sortByLabel(FrameBasedData i,FrameBasedData j);

#endif // UTIL_H
