#ifndef QFRAMEBASEDTABLEMODEL_H
#define QFRAMEBASEDTABLEMODEL_H

#include <QAbstractTableModel>

#include <vector>
using std::vector;

#include <framebaseddata.h>

class QFrameBasedTableModel : public QAbstractTableModel
{
    Q_OBJECT
/// https://doc.qt.io/archives/4.6/itemviews-addressbook.html

public:
    int sortFlag = 0;
    explicit QFrameBasedTableModel(QObject* _parent = 0);
    explicit QFrameBasedTableModel(vector<FrameBasedData> &_frameBasedData, QObject* _parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &_parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &_parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &_index, int _role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int _section, Qt::Orientation _orientation, int _role) const Q_DECL_OVERRIDE;

    // Editable:
    bool insertRows(int _row, int _count, const QModelIndex &_parent) Q_DECL_OVERRIDE;
    bool removeRows(int _row, int _count, const QModelIndex &_parent) Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &_index, const QVariant &_value, int _role = Qt::EditRole) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &_index) const Q_DECL_OVERRIDE;

    // Custom methods:
    bool insertRow(const FrameBasedData &_frameBasedData);
    bool changeRow(const FrameBasedData &_frameBasedData, const int _index);
    bool removeRow(const int _index);
    bool clear();
    void setFrameBasedData(vector<FrameBasedData> &_frameBasedData);
    vector<FrameBasedData>* getFrameBasedData();

private:
    vector<FrameBasedData>* frameData;

public slots:
   void slot_sortTable(int);
};

class sortingMethods
{
public:
    bool static sortByIniFrame(FrameBasedData i,FrameBasedData j);
    bool static sortByEndFrame(FrameBasedData i,FrameBasedData j);
    bool static sortByName(FrameBasedData i,FrameBasedData j);
    bool static sortByCategory(FrameBasedData i,FrameBasedData j);
    bool static sortByLabel(FrameBasedData i,FrameBasedData j);
};

#endif // QFRAMEBASEDTABLEMODEL_H
