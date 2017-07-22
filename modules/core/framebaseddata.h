#ifndef FRAMEBASEDDATA_H
#define FRAMEBASEDDATA_H

#include <iostream>
using std::string;

#include "data.h"

enum mode
{
    insert,
    alter,
    discard
};

class FrameBasedData : public Data
{
public:
    FrameBasedData();
    FrameBasedData(const unsigned int &_id);

    FrameBasedData(const string &_category,
                   const string &_info,
                   const string &_label,
                   const string &_name,
                   const unsigned int &_ini,
                   const unsigned int &_end);

    FrameBasedData(const unsigned int &_id,
                   const string &_category,
                   const string &_info,
                   const string &_label,
                   const string &_name,
                   const unsigned int &_ini,
                   const unsigned int &_end);

    unsigned int getInitialFrameId() const;
    unsigned int getFinalFrameId() const;

    void setInitialFrameId(const unsigned int _ini);
    void setFinalFrameId(const unsigned int _end);

    void operator=(const FrameBasedData &_frameBasedData);

private:
    unsigned int initialFrameId;
    unsigned int finalFrameId;
};

#endif // FRAMEBASEDDATA_H
