#ifndef FRAMEBASEDDATA_H
#define FRAMEBASEDDATA_H

#include <iostream>
using std::string;

enum mode
{
    insert,
    alter,
    discard
};

class FrameBasedData
{
public:
    FrameBasedData();

    FrameBasedData(const int _iniFrame,
                   const int _endFrame,
                   const string &_category,
                   const string &_label,
                   const string &_info);

    FrameBasedData(const int _identifier,
                   const int _iniFrame,
                   const int _endFrame,
                   const string &_category,
                   const string &_label,
                   const string &_info);

    int getIdentifier() const;
    int getInitialFrameId() const;
    int getFinalFrameId() const;
    string getCategory() const;
    string getLabel() const;
    string getInfo() const;

    void setIdentifier(const int _id);
    void setInitialFrameId(const int _ini);
    void setFinalFrameId(const int _end);
    void setCategory(const string &_category);
    void setLabel(const string &_label);
    void setInfo(const string &_info);

private:
    int identifier;
    int initialFrameId;
    int finalFrameId;
    string category;
    string label;
    string info;
};

#endif // FRAMEBASEDDATA_H
