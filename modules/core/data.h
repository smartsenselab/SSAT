#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
using std::multimap;
using std::string;
using std::vector;

class Data
{
public:
    Data();
    Data(const unsigned int &_id, const string &_name);

    unsigned int getId() const;
    vector<string> getAttributes(const string &_key) const;
    vector<string> getInfo() const;
    string getLabel() const;
    string getName() const;

    void addAttributes(const string &_key, const string &_attr);
    void delAttributes(const string &_key);
    void delAttributes();
    void addInfo(const string &_info);
    void delInfo(const unsigned int _index);
    void delInfo();

    void setId(const unsigned int &_id);
    void setLabel(const string &_label);
    void setName(const string &_name);

    void operator=(const Data &_data);

protected:
    unsigned int id;
    multimap<string, string> attributes;
    vector<string> info;
    string label;
    string name;
};

/*
 * trocar labels por info
 * string labels
 * multimap<string> attributes
 */

#endif // DATA_H
