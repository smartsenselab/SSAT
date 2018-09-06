#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <algorithm>
#include <iterator>
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
    vector< vector<string> > getAttributesPath();

    bool isBranch();
    bool isLeaf();
    bool isRoot();

protected:
    void scanTree(Attribute *_mainNode, Attribute *_currentNode, vector< vector<string> > &_paths);

protected:
    bool root;
    string name;
    Attribute* parent;
    vector<Attribute*> children;
};

#endif // ATTRIBUTE_H
