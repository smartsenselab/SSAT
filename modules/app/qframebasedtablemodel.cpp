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
    if(!_parent.isValid())
    {
        return 0;
    }
    return static_cast<int>(this->frameData->size());
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
    std::cout << "Entrou no DATA" << std::endl;
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
        case 0:
            return 1; //QString("Column 1");
        case 1:
            return 2; //QString("Column 2");
        case 2:
            return 3; //QString("Column 3");
        case 3:
            return 4; //QString("Column 4");
        case 4:
            return 5; //QString("Column 5");
        }
    }
    else if(_role == Qt::EditRole)
    {
        switch(_index.column())
        {
        case 0:
            return QString::fromStdString(this->frameData->at(static_cast<unsigned long>(_index.row())).getName());
        case 1:
            return QString::fromStdString(this->frameData->at(static_cast<unsigned long>(_index.row())).getCategory());
        case 2:
            return QString::fromStdString(this->frameData->at(static_cast<unsigned long>(_index.row())).getLabel());
        case 3:
            return this->frameData->at(static_cast<unsigned long>(_index.row())).getInitialFrameId();
        case 4:
            return this->frameData->at(static_cast<unsigned long>(_index.row())).getFinalFrameId();
        }
    }

    return QVariant();
}

bool QFrameBasedTableModel::setData(const QModelIndex &_index, const QVariant &_value, int _role)
{
    if (_index.isValid() && _role == Qt::EditRole)
    {
        switch(_index.column())
        {
        case 0:
            if(_value.toString().isEmpty())
            {
                return false;
            }
            this->frameData->at(static_cast<unsigned long>(_index.row())).setName(_value.toString().toStdString());
            break;
        case 1:
            if(_value.toString().isEmpty())
            {
                return false;
            }
            this->frameData->at(static_cast<unsigned long>(_index.row())).setCategory(_value.toString().toStdString());
            break;
        case 2:
            if(_value.toString().isEmpty())
            {
                return false;
            }
            this->frameData->at(static_cast<unsigned long>(_index.row())).setLabel(_value.toString().toStdString());
            break;
        case 3:
            if(_value.toInt() < 0)
            {
                return false;
            }
            this->frameData->at(static_cast<unsigned long>(_index.row())).setInitialFrameId(_value.toInt());
            break;
        case 4:
            if(_value.toInt() < 0)
            {
                return false;
            }
            this->frameData->at(static_cast<unsigned long>(_index.row())).setFinalFrameId(_value.toInt());
            break;
        }
        return true;
    }
    return false;

    //    if(data(_index, _role) != _value)
    //    {
    //        // FIXME: Implement me!
    //        emit this->dataChanged(_index, _index, QVector<int>() << _role);
    //        return true;
    //    }
    //    return false;
}

Qt::ItemFlags QFrameBasedTableModel::flags(const QModelIndex &_index) const
{
    if (!_index.isValid())
    {
        return Qt::NoItemFlags;
    }

    //    return Qt::ItemIsEditable; // FIXME: Implement me!

    Qt::ItemFlags flags = QAbstractItemModel::flags(_index);
    flags |= (Qt::ItemIsEditable
              |Qt::ItemIsSelectable
              |Qt::ItemIsUserCheckable
              |Qt::ItemIsEnabled
              |Qt::ItemIsDragEnabled
              |Qt::ItemIsDropEnabled);
    return flags;
}

void QFrameBasedTableModel::setFrameBasedData(vector<FrameBasedData> &_frameBasedData)
{
    this->frameData = &(_frameBasedData);

    std::cout << "Copiando core para QFrameBasedTableModel: " << this->frameData->size() << std::endl;
}

vector<FrameBasedData>* QFrameBasedTableModel::getFrameBasedData()
{
    return this->frameData;
}
