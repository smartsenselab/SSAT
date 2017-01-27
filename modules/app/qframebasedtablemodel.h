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
    ///
    /// \brief QFrameBasedTableModel Constructor for a empty table model
    /// \param _parent parent of the model
    ///
    explicit QFrameBasedTableModel(QObject* _parent = 0);
    ///
    /// \brief QFrameBasedTableModel Constructor for a table model that has elements
    /// \param _frameBasedData elements that will be put in the table model
    /// \param _parent parent of the model
    ///
    explicit QFrameBasedTableModel(vector<FrameBasedData> &_frameBasedData, QObject* _parent = 0);

    // Basic functionality:
    int rowCount(const QModelIndex &_parent = QModelIndex()) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &_parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &_index, int _role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    QVariant headerData(int _section, Qt::Orientation _orientation, int _role) const Q_DECL_OVERRIDE;

    // Editable:
    ///
    /// \brief insertRows insert rows in the model
    /// \param _row
    /// \param _count
    /// \param _parent
    /// \return true for success false for failure
    ///
    bool insertRows(int _row, int _count, const QModelIndex &_parent) Q_DECL_OVERRIDE;
    bool removeRows(int _row, int _count, const QModelIndex &_parent) Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &_index, const QVariant &_value, int _role = Qt::EditRole) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &_index) const Q_DECL_OVERRIDE;

    // Custom methods:
    ///
    /// \brief insertRow insert a row in the table
    /// \param _frameBasedData data to be inserted
    /// \return true for success false for failure
    ///
    bool insertRow(const FrameBasedData &_frameBasedData);
    ///
    /// \brief changeRow change one row in the table
    /// \param _frameBasedData data to insert in the table
    /// \param _index index of the row to be changed
    /// \return  true for success false for failure
    ///
    bool changeRow(const FrameBasedData &_frameBasedData, const int _index);
    ///
    /// \brief removeRow delete a row pointed by index
    /// \param _index index of the row to be removed
    /// \return  true for success false for failure
    ///
    bool removeRow(const int _index);
    ///
    /// \brief clear clear the table
    /// \return true for success false for failure
    ///
    bool clear();
    void setFrameBasedData(vector<FrameBasedData> &_frameBasedData);
    vector<FrameBasedData>* getFrameBasedData();

private:
    ///
    /// \brief frameData vector containing the data in the table
    ///
    vector<FrameBasedData>* frameData;

public slots:
    ///
    /// \brief slot_sortTable sort the table
    ///
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
