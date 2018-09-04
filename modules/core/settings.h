#ifndef SETTINGS_H
#define SETTINGS_H

#include <set>
#include <string>
#include <vector>
using std::set;
using std::string;
using std::vector;

class Settings
{
public:
    Settings();

    unsigned int getLargestId();
    string getLatestCategory();
    string getLatestLabel();
    unsigned int getLatestKey();
    unsigned int getLatestId();

    bool setLargestId(unsigned int _id);
    void setLatestCategory(string _category);
    void setLatestLabel(string _label);
    void setLatestKey(unsigned int _key);
    void setLatestId(unsigned int _id);

public:
    set<unsigned int> tracklets;

private:
    string latestCategory;
    string latestLabel;
    unsigned int latestId;
    unsigned int latestKey;
};

#endif // SETTINGS_H
