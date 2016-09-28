#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>

using namespace std;

class Data
{
public:
    Data();
    Data(const string &_id, const string &_label);

    string getId() const;
    string getLabel() const;

    void setId(const string &_id);
    void setLabel(const string &_label);

protected:
    unsigned int frameId;
    string id;
    string label;
};

#endif // DATA_H
