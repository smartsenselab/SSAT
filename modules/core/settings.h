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

    string getCurrentSeparator() const;
    string getLatestCategory() const;
    string getLatestLabel() const;
    unsigned int getFrameSkip() const;
    unsigned int getLargestId() const;
    unsigned int getLatestKey() const;
    unsigned int getLatestId() const;


    void setCurrentSeparator(string _separator);
    void setLatestCategory(string _category);
    void setLatestLabel(string _label);
    void setFrameSkip(unsigned int _frameSkip);
    bool setLargestId(unsigned int _id);
    void setLatestKey(unsigned int _key);
    void setLatestId(unsigned int _id);

public:
    set<unsigned int> tracklets;

private:
    string curretSeparator;
    string latestCategory;
    string latestLabel;
    unsigned int frameSkip;
    unsigned int latestId;
    unsigned int latestKey;
};

#endif // SETTINGS_H
