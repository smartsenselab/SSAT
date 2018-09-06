#include "attribute.h"

Attribute::Attribute()
{
    this->name = "ROOT";
    this->parent = NULL;
    this->root = true;

    this->addChild("Rafael")->addChild("Henrique")->addChild("Vareto");
    this->addChild("Rafael")->addChild("Gomes")->addChild("Costa");
    this->addChild("Luisa")->addChild("Aimee")->addChild("Vargas")->addChild("Quirino");
}

Attribute::Attribute(string _name, bool _root)
{
    this->name = _name;
    this->parent = NULL;
    this->root = _root;
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

void Attribute::setNodeName(const string _name)
{
    this->name = _name;
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
    vector<Attribute *>::iterator childIt;
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

vector< vector<string> > Attribute::getAttributesPath()
{
    Attribute *mainNode = this;
    vector<Attribute*> children = mainNode->getChildren();
    vector< vector<string> > attribute_paths;

    vector<Attribute*>::iterator childIt;
    for(childIt = children.begin(); childIt != children.end(); childIt++)
    {
        this->scanTree(mainNode, *childIt, attribute_paths);
    }
    return attribute_paths;
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

void Attribute::scanTree(Attribute *_mainNode, Attribute *_currentNode, vector< vector<string> > &_paths)
{
    if(_currentNode != NULL)
    {
        if(_currentNode->isLeaf())
        {
            vector<string> path;
            Attribute *rewindNode = _currentNode;
            while( (rewindNode != NULL) && (rewindNode != _mainNode) )
            {
                path.push_back(rewindNode->getNodeName());
                rewindNode = rewindNode->getParent();
            }
            std::reverse(std::begin(path), std::end(path));
            _paths.push_back(path);
        }
        else
        {
            vector<Attribute*> children = _currentNode->getChildren();

            vector<Attribute*>::iterator childIt;
            for(childIt = children.begin(); childIt != children.end(); childIt++)
            {
                this->scanTree(_mainNode, *childIt, _paths);
            }
        }
    }
}
