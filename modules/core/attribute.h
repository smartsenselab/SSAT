#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Attribute
{
public:
    Attribute(string);
    ~Attribute();
    void clear();

    string getNodeName();
    vector<string> getChildrenNames();

    Attribute* addChild(const string);
    Attribute* addChild(Attribute*);
    Attribute* getParent();
    Attribute* getNode();

    vector<Attribute*> findChildren(const string);
    vector<Attribute*> getChildren();

    bool isBranch();
    bool isLeaf();
    bool isRoot();

protected:
    string name;
    Attribute* parent;
    vector<Attribute*> children;
};

#endif // ATTRIBUTE_H
