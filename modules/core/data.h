#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>
using std::multimap;
using std::unordered_multimap;
using std::string;
using std::vector;

class Data
{
public:
    Data();
    Data(const string &_name);
    Data(const unsigned int &_id, const string &_name);

    unsigned int getId() const;
    vector<string> getAttributes(const string &_key) const;
    vector<string> getComments() const;
    string getName() const;

    void addAttributes(const string &_key, const string &_attr);
    void delAttributes(const string &_key);
    void delAttributes();
    void addComments(const string &_info);
    void delComments(const unsigned int _index);
    void delComments();

    void setId(const unsigned int &_id);
    void setName(const string &_name);

    void operator=(const Data &_data);

protected:
    multimap<string, string> attributes;
    vector<string> comments;
    unsigned int id;
    string name;
};

/*
 * trocar labels por info
 * string labels
 * multimap<string> attributes
 */

#endif // DATA_H
