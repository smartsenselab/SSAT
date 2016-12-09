#include "util.h"

bool sortByIniFrame(FrameBasedData i,FrameBasedData j)
{
    return (i.getInitialFrameId() < j.getInitialFrameId());
}

bool sortByEndFrame(FrameBasedData i,FrameBasedData j)
{
    return (i.getFinalFrameId() < j.getFinalFrameId());
}

bool sortByName(FrameBasedData i,FrameBasedData j)
{
    return strcmp(i.getName().c_str(), j.getName().c_str()) < 0;
}

bool sortByCategory(FrameBasedData i,FrameBasedData j)
{
    return strcmp(i.getCategory().c_str(), j.getCategory().c_str()) < 0;
}

bool sortByLabel(FrameBasedData i,FrameBasedData j)
{
    return strcmp(i.getLabel().c_str(), j.getLabel().c_str()) < 0;
}
