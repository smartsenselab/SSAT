#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

class Data
{
public:
    Data();
    Data(const unsigned int &_id, const string &_name);

    unsigned int getId() const;
    string getLabels(const unsigned int _index) const;
    vector<string> getLabels() const;
    string getName() const;

    void setId(const unsigned int &_id);
    void setLabels(const string &_label);
    void setName(const string &_name);

    void operator=(const Data &_data);

protected:
    unsigned int id;
    vector<string> labels;
    string name;
};

#endif // DATA_H
