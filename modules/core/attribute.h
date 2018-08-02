#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <vector>
using std::string;
using std::vector;

class Attribute
{
public:
    Attribute();
    Attribute(string _name, bool _root = false);
    ~Attribute();
    void clear();

    string getNodeName();
    vector<string> getChildrenNames();

    void setNodeName(const string _name);

    Attribute* addChild(const string _name);
    Attribute* addChild(Attribute* _child);
    Attribute* getParent();
    Attribute* getNode();

    Attribute* findChild(const string _name);
    vector<Attribute*> getChildren();

    bool isBranch();
    bool isLeaf();
    bool isRoot();

protected:
    bool root;
    string name;
    Attribute* parent;
    vector<Attribute*> children;
};

#endif // ATTRIBUTE_H
