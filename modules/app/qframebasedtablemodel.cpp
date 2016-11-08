#include "qframebasedtablemodel.h"

QFrameBasedTableModel::QFrameBasedTableModel(QObject *_parent)
    : QAbstractTableModel(_parent)
{
}

int QFrameBasedTableModel::rowCount(const QModelIndex &_parent) const
{
    if(!_parent.isValid())
    {
        return 0;
    }
    return static_cast<int>(this->frameData.size());
}

int QFrameBasedTableModel::columnCount(const QModelIndex &_parent) const
{
    if(!_parent.isValid())
    {
        return 0;
    }
    return 5;
}

QVariant QFrameBasedTableModel::data(const QModelIndex &_index, int _role) const
{
    if(!_index.isValid())
    {
        return QVariant();
    }

    // FIXME: Implement me!
    return QVariant();
}

bool QFrameBasedTableModel::setData(const QModelIndex &_index, const QVariant &_value, int _role)
{
    if(data(_index, _role) != _value)
    {
        // FIXME: Implement me!
        emit this->dataChanged(_index, _index, QVector<int>() << _role);
        return true;
    }
    return false;
}

Qt::ItemFlags QFrameBasedTableModel::flags(const QModelIndex &_index) const
{
    if (!_index.isValid())
    {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

void QFrameBasedTableModel::setFrameBasedData(const vector<FrameBasedData> &_frameBasedData)
{
    this->frameData = _frameBasedData;
}
