#include "qframebasedtablemodel.h"

QFrameBasedTableModel::QFrameBasedTableModel(QObject *_parent)
    : QAbstractTableModel(_parent)
{
}

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
    return 5;
}

QVariant QFrameBasedTableModel::data(const QModelIndex &_index, int _role) const
{
    if(!_index.isValid())
    {
        return QVariant();
    }

    if((_index.row() >= static_cast<int>(this->frameData->size())) || (_index.row() < 0))
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
                                              static_cast<unsigned long>(_index.row())).getName());
        case 1:
            return QString::fromStdString(this->frameData->at(
                                              static_cast<unsigned long>(_index.row())).getCategory());
        case 2:
            return QString::fromStdString(this->frameData->at(
                                              static_cast<unsigned long>(_index.row())).getLabel());
        case 3:
            return this->frameData->at(static_cast<unsigned long>(_index.row())).getInitialFrameId();
        case 4:
            return this->frameData->at(static_cast<unsigned long>(_index.row())).getFinalFrameId();
        default:
            return QString("Error");
        }
    }
    //    else if(_role == Qt::EditRole)
    //    {
    //        switch(_index.column())
    //        {
    //        case 0:
    //            return QString::fromStdString(this->frameData->at(static_cast<unsigned long>(_index.row())).getName());
    //        case 1:
    //            return QString::fromStdString(this->frameData->at(static_cast<unsigned long>(_index.row())).getCategory());
    //        case 2:
    //            return QString::fromStdString(this->frameData->at(static_cast<unsigned long>(_index.row())).getLabel());
    //        case 3:
    //            return this->frameData->at(static_cast<unsigned long>(_index.row())).getInitialFrameId();
    //        case 4:
    //            return this->frameData->at(static_cast<unsigned long>(_index.row())).getFinalFrameId();
    //        }
    //    }

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
                return tr("Name");
            case 1:
                return tr("Category");
            case 2:
                return tr("Label");
            case 3:
                return tr("Ini Frame");
            case 4:
                return tr("End Frame");
            default:
                return tr("ERROR");
            }
        }
        else if(_orientation == Qt::Vertical)
        {
            return _section + 1;
        }
    }

    return QVariant::Invalid;
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
                    .setName(_value.toString().toStdString());
            break;
        case 1:
            if(_value.toString().isEmpty())
                return false;
            this->frameData->at(static_cast<unsigned long>(_index.row()))
                    .setCategory(_value.toString().toStdString());
            break;
        case 2:
            if(_value.toString().isEmpty())
                return false;
            this->frameData->at(static_cast<unsigned long>(_index.row()))
                    .setLabel(_value.toString().toStdString());
            break;
        case 3:
            if(_value.toInt() < 0)
                return false;
            this->frameData->at(static_cast<unsigned long>(_index.row()))
                    .setInitialFrameId(_value.toInt());
            break;
        case 4:
            if(_value.toInt() < 0)
                return false;
            this->frameData->at(static_cast<unsigned long>(_index.row()))
                    .setFinalFrameId(_value.toInt());
            break;
        }

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

    Qt::ItemFlags flags = QAbstractItemModel::flags(_index);
    flags |= ( Qt::ItemIsSelectable
              //|Qt::ItemIsEditable
              |Qt::ItemIsUserCheckable
              |Qt::ItemIsEnabled
              |Qt::ItemIsDragEnabled
              |Qt::ItemIsDropEnabled);

    return flags;
}

void QFrameBasedTableModel::setFrameBasedData(vector<FrameBasedData> &_frameBasedData)
{
    this->frameData = &(_frameBasedData);
}

vector<FrameBasedData>* QFrameBasedTableModel::getFrameBasedData()
{
    return this->frameData;
}
