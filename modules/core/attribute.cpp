#include "attribute.h"

Attribute::Attribute(string _name)
{
    this->name = _name;
    this->parent = NULL;
}

Attribute::~Attribute()
{
    this->clear();
}

void Attribute::clear()
{
    vector<Attribute*>::iterator childIt;
    for(childIt = this->children.begin(); childIt != this->children.end(); childIt++)
    {
        if(*childIt)
        {
            (*childIt)->clear();
            delete *childIt;
        }
    }

    this->children.clear();
}

string Attribute::getNodeName()
{
    return this->name;
}

vector<string> Attribute::getChildrenNames()
{
    vector<string> names;
    vector<Attribute*>::iterator childIt;
    for(childIt = this->children.begin(); childIt != this->children.end(); childIt++)
    {
        names.push_back((*childIt)->getNodeName());
    }

    return names;
}

Attribute* Attribute::addChild(const std::string _name)
{
    Attribute* child = new Attribute(_name);
    child->parent = this;
    this->children.push_back(child);

    return child;
}

Attribute* Attribute::addChild(Attribute* _child)
{
    _child->parent = this;
    this->children.push_back(_child);

    return _child;
}

Attribute* Attribute::getParent()
{
    return (*this).parent;
}

Attribute* Attribute::getNode()
{
    return this;
}

vector<Attribute*> Attribute::findChildren(const string _name)
{
    vector<Attribute*> children;
    vector<Attribute*>::iterator childIt;
    for(childIt = this->children.begin(); childIt != this->children.end(); childIt++)
    {
        if (_name.compare((*childIt)->getNodeName()) == 0)
        {
            children.push_back(*childIt);
        }
    }

    return children;
}

vector<Attribute*> Attribute::getChildren()
{
    vector<Attribute*> children;
    vector<Attribute*>::iterator childIt;
    for(childIt = this->children.begin(); childIt != this->children.end(); childIt++)
    {
        children.push_back(*childIt);
    }

    return children;
}


bool Attribute::isBranch()
{
    return ((this->children.size() > 0) && (this->parent != NULL));
}

bool Attribute::isLeaf()
{
    return (this->children.size() == 0);
}

bool Attribute::isRoot()
{
    return (this->parent == NULL);
}
