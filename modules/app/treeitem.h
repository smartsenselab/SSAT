#ifndef TREEITEM_H
#define TREEITEM_H

#include <QCoreApplication>
#include <QVariant>

class TreeItem
{
public:
    TreeItem(const QList<QVariant> &_data, TreeItem* _parent = 0);
    ~TreeItem();

    bool isParent() const;

    int childCount() const;
    int columnCount() const;
    int row() const;

    QVariant data(int _column) const;

    TreeItem* child(int _row);
    TreeItem* parentItem();

    void appendChild(TreeItem* _child);
    void setParent(const bool _value);

private:
    bool parent;

    QList<QVariant> modelItemData;
    QList<TreeItem*> modelChildItems;
    TreeItem *modelParentItem;
};

#endif // TREEITEM_H
