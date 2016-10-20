#include "treeitem.h"

TreeItem::TreeItem(const QList<QVariant> &_data, TreeItem* _parent)
{
    this->modelItemData = _data;
    this->modelParentItem = _parent;
}

TreeItem::~TreeItem()
{
    qDeleteAll(this->modelChildItems);
}

bool TreeItem::isParent() const
{
    return this->parent;
}

int TreeItem::childCount() const
{
    return this->modelChildItems.count();
}

int TreeItem::columnCount() const
{
    return this->modelItemData.count();
}

int TreeItem::row() const
{
    if(this->modelParentItem)
    {
        return this->modelParentItem->modelChildItems.indexOf(const_cast<TreeItem*>(this));
    }
    return 0;
}

QVariant TreeItem::data(int _column) const
{
    return this->modelItemData.value(_column);
}

TreeItem* TreeItem::child(int _row)
{
    return this->modelChildItems.value(_row);
}

TreeItem* TreeItem::parentItem()
{

}

void TreeItem::appendChild(TreeItem* _child)
{
    if(this->parent)
    {
        this->modelChildItems.append(_child);
    }
}

void TreeItem::setParent(const bool _parent)
{
    this->parent = _parent;
}
