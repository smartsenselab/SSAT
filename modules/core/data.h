#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using std::multimap;
using std::string;
using std::stringstream;
using std::vector;

class Data
{
public:
    Data();
    Data(const unsigned int &_id);
    Data(const unsigned int &_id, const unsigned int &_key);

    Data(const string &_category,
         const string &_info,
         const string &_label,
         const string &_name);

    Data(const unsigned int &_id,
         const string &_category,
         const string &_info,
         const string &_label,
         const string &_name);

    Data(const unsigned int &_id,
         const unsigned int &_key,
         const string &_category,
         const string &_info,
         const string &_label,
         const string &_name);

    unsigned int getId() const;
    unsigned int getKey() const;
    string getCategory() const;
    string getInfo() const;
    string getLabel() const;
    string getName() const;

    void setId(const unsigned int &_id);
    void setKey(const unsigned int &_key);
    void setCategory(const string &_category);
    void setInfo(const string &_info);
    void setLabel(const string &_label);
    void setName(const string &_name);

    void operator=(const Data &_data);

protected:
    vector<string> splitIntoTokens(const string &_category, const string &_delimiter="->");
    string mergeIntoString(const vector<string> &_category, const string &_delimiter="->") const;

protected:
    unsigned int id;
    unsigned int key;
    string category;
    string info;
    string label;
    string name;
};

#endif // DATA_H
