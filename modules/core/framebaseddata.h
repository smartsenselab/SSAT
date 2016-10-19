#ifndef FRAMEBASEDDATA_H
#define FRAMEBASEDDATA_H

#include <iostream>
using std::string;

class FrameBasedData
{
public:
    FrameBasedData();
    FrameBasedData(const int _iniFrame,
                   const int _endFrame,
                   const string &_category,
                   const string &_label,
                   const string &_name);

    int getInitialFrameId() const;
    int getFinalFrameId() const;
    string getCategory() const;
    string getLabel() const;
    string getName() const;

    void setInitialFrameId(const int _id);
    void setFinalFrameId(const int _id);
    void setCategory(const string &_category);
    void setLabel(const string &_label);
    void setName(const string &_name);

private:
    int initialFrameId;
    int finalFrameId;
    string category;
    string label;
    string name;
};

#endif // FRAMEBASEDDATA_H
