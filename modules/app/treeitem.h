#ifndef TREEITEM_H
#define TREEITEM_H

#include <QCoreApplication>
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QVector>

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant> &_data, TreeItem* _parent = 0);
    ~TreeItem();

    bool isCategory() const;

    bool insertChildren(int _position, int _count, int _columns);
    bool insertColumns(int _position, int _columns);
    bool removeChildren(int _position, int _count);
    bool removeColumns(int _position, int _columns);
    bool setData(int _column, const QVariant &_value);

    int childCount() const;
    int childNumber() const;
    int columnCount() const;

    QVariant data(int _column) const;

    TreeItem* child(int _row);
    TreeItem* parent();

    void isCategory(const bool _value);

private:
    bool category;

    QList<TreeItem*> childItems;
    QVector<QVariant> itemData;
    TreeItem *parentItem;
};

#endif // TREEITEM_H
