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
    explicit QFrameBasedTableModel(QObject *_parent = 0);
    explicit QFrameBasedTableModel(vector<FrameBasedData> &_frameBasedData, QObject *_parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &_parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &_parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &_index, int _role = Qt::DisplayRole) const override;
    QVariant headerData(int _section, Qt::Orientation _orientation, int _role) const override;

    // Editable:
    bool setData(const QModelIndex &_index, const QVariant &_value, int _role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &_index) const override;

    // Custom methods:
    void setFrameBasedData(vector<FrameBasedData> &_frameBasedData);
    vector<FrameBasedData>* getFrameBasedData();

private:
    vector<FrameBasedData>* frameData;
};

#endif // QFRAMEBASEDTABLEMODEL_H
