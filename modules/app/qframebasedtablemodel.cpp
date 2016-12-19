#include "qframebasedtablemodel.h"

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
    return 5;
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
    return this->removeRows(0, this->rowCount(), QModelIndex());
}

void QFrameBasedTableModel::setFrameBasedData(vector<FrameBasedData> &_frameBasedData)
{
    this->frameData = &(_frameBasedData);
}

vector<FrameBasedData>* QFrameBasedTableModel::getFrameBasedData()
{
    return this->frameData;
}

int flag1 = 0;

struct IniFrame {
  bool operator() (FrameBasedData i,FrameBasedData j) {
      if(flag1 == 0){
          return (i.getInitialFrameId() < j.getInitialFrameId());
      }
      else{
          return (i.getInitialFrameId() > j.getInitialFrameId());
      }
  }
} IniFrame;


struct FinalFrame {
  bool operator() (FrameBasedData i,FrameBasedData j) {
      if(flag1 == 0){
          return (i.getFinalFrameId() < j.getFinalFrameId());
      }
      else{
          return (i.getFinalFrameId() > j.getFinalFrameId());
      }
  }
} FinalFrame;


struct Name {
  bool operator() (FrameBasedData i,FrameBasedData j) {
      if(flag1 == 0){
          return strcmp(i.getName().c_str(), j.getName().c_str()) < 0;
      }
      else{
          return strcmp(i.getName().c_str(), j.getName().c_str()) > 0;
      }
  }
} Name;

struct Category {
  bool operator() (FrameBasedData i,FrameBasedData j) {
      if(flag1 == 0){
          return strcmp(i.getCategory().c_str(), j.getCategory().c_str()) < 0;
      }
      else{
          return strcmp(i.getCategory().c_str(), j.getCategory().c_str()) > 0;
      }
  }
} Category;

struct Label {
  bool operator() (FrameBasedData i,FrameBasedData j) {
      if(flag1 == 0){
          return strcmp(i.getLabel().c_str(), j.getLabel().c_str()) < 0;
      }
      else{
          return strcmp(i.getLabel().c_str(), j.getLabel().c_str()) > 0;
      }
  }
} Label;

void QFrameBasedTableModel::slot_SortTable(int index){
     int size = this->frameData->size();
     if(index == 3){
         std::sort(this->frameData->begin(), this->frameData->end(), IniFrame);
     }
     else if( index == 4){
        std::sort(this->frameData->begin(), this->frameData->end(), FinalFrame);
     }
     else if( index == 0){
         std::sort(this->frameData->begin(), this->frameData->end(), Name);
     }
     else if( index == 1){
          std::sort(this->frameData->begin(), this->frameData->end(), Category);
     }
     else if( index == 2){
         std::sort(this->frameData->begin(), this->frameData->end(), Label);
     }
     flag1 = flag;
     if(flag == 1){ flag = 0;} else {flag = 1;}
     this->dataChanged(QAbstractItemModel::createIndex(0,0), QAbstractItemModel::createIndex(2, size - 1));
}
