#include "qmultimapmodel.h"

QMultiMapModel::QMultiMapModel(QObject *_parent) :
    QAbstractTableModel(_parent)
{
    this->container = NULL;
}

int QMultiMapModel::rowCount(const QModelIndex &_parent) const
{
    if(this->container)
    {
        return this->container->count();
    }

    return 0;
}

int QMultiMapModel::columnCount(const QModelIndex &_parent) const
{
    return 1;
}

QVariant QMultiMapModel::data(const QModelIndex &_index, int _role) const
{
    if (!this->container)
    {
        return QVariant();
    }

    if (_index.row() < 0 || _index.row() >= this->container->count() || _role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (_index.column() == 0)
    {
        return this->container->keys().at(_index.row());
    }

    if (_index.column() == 1)
    {
        return this->container->values().at(_index.row());
    }

    return QVariant();
}

