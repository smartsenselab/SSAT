#include "qframebasedtablemodel.h"
#include <QDebug>
#include <algorithm>

bool static staticFlag = 0;

QFrameBasedTableModel::QFrameBasedTableModel(QObject *_parent)
    : QAbstractTableModel(_parent)
{}

QFrameBasedTableModel::QFrameBasedTableModel(vector<FrameBasedData> &_frameBasedData, QObject *_parent)
    : QAbstractTableModel(_parent)
{
    this->setFrameBasedData(_frameBasedData);
}

int QFrameBasedTableModel::rowCount(const QModelIndex &_parent) const
{
    Q_UNUSED(_parent);
    return static_cast<int>(this->frameData->size());
}

int QFrameBasedTableModel::columnCount(const QModelIndex &_parent) const
{
    Q_UNUSED(_parent);
    return 4;
}

QVariant QFrameBasedTableModel::data(const QModelIndex &_index, int _role) const
{
    if(!_index.isValid())
    {
        return QVariant();
    }

    if(_role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    }
    else if(_role == Qt::DisplayRole)
    {
        switch(_index.column())
        {
        case 0:
            return QString::fromStdString(this->frameData->at(
                                              static_cast<unsigned long>(_index.row())).getCategory());
        case 1:
            return QString::fromStdString(this->frameData->at(
                                              static_cast<unsigned long>(_index.row())).getLabel());
        case 2:
            return this->frameData->at(static_cast<unsigned long>(_index.row())).getInitialFrameId();
        case 3:
            return this->frameData->at(static_cast<unsigned long>(_index.row())).getFinalFrameId();
        }
    }

    return QVariant();
}

QVariant QFrameBasedTableModel::headerData(int _section, Qt::Orientation _orientation, int _role) const
{
    if(_role == Qt::DisplayRole)
    {
        if(_orientation == Qt::Horizontal)
        {
            switch(_section)
            {
            case 0:
                return tr("Category");
            case 1:
                return tr("Label");
            case 2:
                return tr("Ini Frame");
            case 3:
                return tr("End Frame");
            }
        }
        else if(_orientation == Qt::Vertical)
        {
            return _section + 1;
        }
    }

    return QVariant::Invalid;
}

bool QFrameBasedTableModel::insertRows(int _row, int _count, const QModelIndex &_parent)
{
    FrameBasedData tempData = FrameBasedData();

    this->beginInsertRows(_parent, _row, _row + _count - 1);
    for(int index = 0; index < _count; index++)
    {
        this->frameData->push_back(tempData);
    }
    this->endInsertRows();

    return true;
}

bool QFrameBasedTableModel::removeRows(int _row, int _count, const QModelIndex &_parent)
{
    this->beginRemoveRows(_parent, _row, _row + _count - 1);
    this->frameData->erase(this->frameData->begin() + _row, this->frameData->begin() + _row + _count);
    this->endRemoveRows();

    return true;
}

bool QFrameBasedTableModel::setData(const QModelIndex &_index, const QVariant &_value, int _role)
{
    if (_index.isValid() && _role == Qt::EditRole)
    {
        switch(_index.column())
        {
        case 0:
            if(_value.toString().isEmpty())
                return false;
            this->frameData->at(static_cast<unsigned long>(_index.row()))
                    .setCategory(_value.toString().toStdString());
            break;
        case 1:
            if(_value.toString().isEmpty())
                return false;
            this->frameData->at(static_cast<unsigned long>(_index.row()))
                    .setLabel(_value.toString().toStdString());
            break;
        case 2:
            if(_value.toInt() < 0)
                return false;
            this->frameData->at(static_cast<unsigned long>(_index.row()))
                    .setInitialFrameId(_value.toInt());
            break;
        case 3:
            if(_value.toInt() < 0)
                return false;
            this->frameData->at(static_cast<unsigned long>(_index.row()))
                    .setFinalFrameId(_value.toInt());
            break;
        }

        emit this->dataChanged(_index, _index);
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

    Qt::ItemFlags flags = QAbstractItemModel::flags(_index);
    flags |= ( Qt::ItemIsSelectable
               |Qt::ItemIsEnabled);

    return flags;
}

bool QFrameBasedTableModel::insertRow(const FrameBasedData &_frameBasedData)
{
    bool cond = this->insertRows(0, 1, QModelIndex());
    if(cond)
    {
        this->frameData->back() = _frameBasedData;
    }
    return cond;
}

bool QFrameBasedTableModel::changeRow(const FrameBasedData &_frameBasedData, const int _index)
{
    this->frameData->at(static_cast<unsigned long>(_index)) = _frameBasedData;
    return true;
}

bool QFrameBasedTableModel::removeRow(const int _index)
{
    this->removeRows(_index, 1, QModelIndex());
    return false;
}

bool QFrameBasedTableModel::clear()
{
    if(this->frameData != NULL)
    {
        return this->removeRows(0, this->rowCount(), QModelIndex());
    }
    return false;
}

void QFrameBasedTableModel::setFrameBasedData(vector<FrameBasedData> &_frameBasedData)
{
    this->frameData = &(_frameBasedData);
}

vector<FrameBasedData>* QFrameBasedTableModel::getFrameBasedData()
{
    return this->frameData;
}

void QFrameBasedTableModel::slot_sortTable(int _index)
{
    unsigned long size = static_cast<unsigned long>(this->frameData->size());

    if(_index == 0)
    {
        std::sort(this->frameData->begin(), this->frameData->end(), sortingMethods::sortByCategory);
    }
    else if(_index == 1)
    {
        std::sort(this->frameData->begin(), this->frameData->end(), sortingMethods::sortByLabel);
    }
    else if(_index == 2)
    {
        std::sort(this->frameData->begin(), this->frameData->end(), sortingMethods::sortByIniFrame);
    }
    else if(_index == 3)
    {
        std::sort(this->frameData->begin(), this->frameData->end(), sortingMethods::sortByEndFrame);
    }

    staticFlag = this->sortFlag;
    this->sortFlag = !this->sortFlag;
    this->dataChanged(QAbstractItemModel::createIndex(0,0), QAbstractItemModel::createIndex(2, size - 1));
}

bool sortingMethods::sortByIniFrame(FrameBasedData i,FrameBasedData j)
{
    if(staticFlag == 0)
    {
        return (i.getInitialFrameId() < j.getInitialFrameId());
    }
    else
    {
        return (i.getInitialFrameId() > j.getInitialFrameId());
    }
}

bool sortingMethods::sortByEndFrame(FrameBasedData i,FrameBasedData j)
{
    if(staticFlag == 0)
    {
        return (i.getFinalFrameId() < j.getFinalFrameId());
    }
    else
    {
        return (i.getFinalFrameId() > j.getFinalFrameId());
    }
}

bool sortingMethods::sortByName(FrameBasedData i,FrameBasedData j)
{
    if(staticFlag == 0)
    {
        return strcmp(i.getInfo().c_str(), j.getInfo().c_str()) < 0;
    }
    else
    {
        return strcmp(i.getInfo().c_str(), j.getInfo().c_str()) > 0;
    }
}

bool sortingMethods::sortByCategory(FrameBasedData i,FrameBasedData j)
{
    if(staticFlag == 0)
    {
        return strcmp(i.getCategory().c_str(), j.getCategory().c_str()) < 0;
    }
    else
    {
        return strcmp(i.getCategory().c_str(), j.getCategory().c_str()) > 0;
    }
}

bool sortingMethods::sortByLabel(FrameBasedData i,FrameBasedData j)
{
    if(staticFlag == 0)
    {
        return strcmp(i.getLabel().c_str(), j.getLabel().c_str()) < 0;
    }
    else
    {
        return strcmp(i.getLabel().c_str(), j.getLabel().c_str()) > 0;
    }
}
