#include "attribute.h"

Attribute::Attribute()
{
    this->name = "ROOT";
    this->parent = NULL;

    this->addChild("Rafael")->addChild("Henrique")->addChild("Vareto");
    this->addChild("Rafael")->addChild("Gomes")->addChild("Costa");
    this->addChild("Luisa")->addChild("Aimee")->addChild("Vargas")->addChild("Quirino");
}

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
    Attribute* thisChild = this->findChild(_name);

    if(thisChild == NULL)
    {
        Attribute* child = new Attribute(_name);
        child->parent = this;
        this->children.push_back(child);
        return child;
    }
    else
    {
        return thisChild;
    }
}

Attribute* Attribute::addChild(Attribute* _child)
{
    Attribute* thisChild = this->findChild(_child->getNodeName());

    if(thisChild == NULL)
    {
        _child->parent = this;
        this->children.push_back(_child);
        return _child;
    }
    else
    {
        return thisChild;
    }

}

Attribute* Attribute::getParent()
{
    return (*this).parent;
}

Attribute* Attribute::getNode()
{
    return this;
}

Attribute* Attribute::findChild(const string _name)
{
    vector<Attribute*>::iterator childIt;
    for(childIt = this->children.begin(); childIt != this->children.end(); childIt++)
    {
        if (_name.compare((*childIt)->getNodeName()) == 0)
        {
            return (*childIt);
        }
    }

    return NULL;
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
