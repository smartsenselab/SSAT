#include "treeitem.h"

TreeItem::TreeItem(const QVector<QVariant> &_data, TreeItem* _parent)
{
    this->parentItem = _parent;
    this->itemData = _data;
}

TreeItem::~TreeItem()
{
    qDeleteAll(this->childItems);
}

bool TreeItem::isCategory() const
{
    return this->category;
}

bool TreeItem::insertChildren(int _position, int _count, int _columns)
{
    if (_position < 0 || _position > this->childItems.size())
    {
        return false;
    }

    for (int row = 0; row < _count; ++row)
    {
        QVector<QVariant> data(_columns);
        TreeItem *item = new TreeItem(data, this);
        this->childItems.insert(_position, item);
    }

    return true;
}

bool TreeItem::insertColumns(int _position, int _columns)
{
    if (_position < 0 || _position > this->itemData.size())
    {
        return false;
    }

    for (int column = 0; column < _columns; ++column)
    {
        this->itemData.insert(_position, QVariant());
    }

    foreach (TreeItem *child, childItems)
    {
        child->insertColumns(_position, _columns);
    }

    return true;
}

bool TreeItem::removeChildren(int _position, int _count)
{
    if (_position < 0 || _position + _count > this->childItems.size())
    {
        return false;
    }

    for (int row = 0; row < _count; ++row)
    {
        delete this->childItems.takeAt(_position);
    }

    return true;
}

bool TreeItem::removeColumns(int _position, int _columns)
{
    if (_position < 0 || _position + _columns > this->itemData.size())
    {
        return false;
    }

    for (int column = 0; column < _columns; ++column)
    {
        this->itemData.remove(_position);
    }

    foreach (TreeItem *child, childItems)
    {
        child->removeColumns(_position, _columns);
    }

    return true;
}

bool TreeItem::setData(int _column, const QVariant &_value)
{
    if (_column < 0 || _column >= this->itemData.size())
    {
        return false;
    }

    this->itemData[_column] = _value;
    return true;
}

int TreeItem::childCount() const
{
    return this->childItems.count();
}

int TreeItem::childNumber() const
{
    if(this->parentItem)
    {
        return this->parentItem->childItems.indexOf(const_cast<TreeItem*>(this));
    }

    return 0;
}

int TreeItem::columnCount() const
{
    return this->itemData.count();
}

QVariant TreeItem::data(int _column) const
{
    return this->itemData.value(_column);
}

TreeItem* TreeItem::child(int _row)
{
    return this->childItems.value(_row);
}

TreeItem* TreeItem::parent()
{
    return this->parentItem;
}

void TreeItem::isCategory(const bool _value)
{
    this->category = _value;
}
