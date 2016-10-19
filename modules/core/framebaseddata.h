#ifndef FRAMEBASEDDATA_H
#define FRAMEBASEDDATA_H

#include <iostream>
using std::string;

class FrameBasedData
{
public:
    FrameBasedData();
    FrameBasedData(const unsigned int _iniFrame,
                   const unsigned int _endFrame,
                   const string &_category,
                   const string &_label,
                   const string &_name);

    unsigned int getInitialFrameId() const;
    unsigned int getFinalFrameId() const;
    string getCategory() const;
    string getLabel() const;
    string getName() const;

    void setInitialFrameId(const unsigned int _id);
    void setFinalFrameId(const unsigned int _id);
    void setCategory(const string &_category);
    void setLabel(const string &_label);
    void setName(const string &_name);

private:
    unsigned int initialFrameId;
    unsigned int finalFrameId;
    string category;
    string label;
    string name;
};

#endif // FRAMEBASEDDATA_H
