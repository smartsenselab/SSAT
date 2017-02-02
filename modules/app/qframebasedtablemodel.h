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
    ///
    /// \brief rowCount Returns the number of rows under the given parent. When the parent is valid it means that rowCount is returning the number of children of parent.
    /// \param _parent Parent is used to locate data in a data model.
    /// \return Returns the number of rows under the given parent.
    ///
    int rowCount(const QModelIndex &_parent = QModelIndex()) const Q_DECL_OVERRIDE;

    ///
    /// \brief columnCount Returns the number of columns for the children of the given parent.
    /// \param _parent Parent is used to locate data in a data model.
    /// \return Returns the number of columns under the given parent.
    ///
    int columnCount(const QModelIndex &_parent = QModelIndex()) const Q_DECL_OVERRIDE;

    ///
    /// \brief data Returns the data stored under the given role for the item referred to by the index.
    /// \param _index Index is used to locate data in a data model.
    /// \param _role The key data to be rendered in the form of text.
    /// \return
    ///
    QVariant data(const QModelIndex &_index, int _role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

    ///
    /// \brief headerData Returns the data for the given role and section in the header with the specified orientation.
    /// \param _section For horizontal headers, the section number corresponds to the column number. Similarly, for vertical headers, the section number corresponds to the row number.
    /// \param _orientation
    /// \param _role
    /// \return
    ///
    QVariant headerData(int _section, Qt::Orientation _orientation, int _role) const Q_DECL_OVERRIDE;

    // Editable:
    ///
    /// \brief insertRows insert rows in the model (overrided function)
    /// \param _row row to be inserted
    /// \param _count count of rows
    /// \param _parent
    /// \return true for success false for failure
    ///
    bool insertRows(int _row, int _count, const QModelIndex &_parent) Q_DECL_OVERRIDE;

    ///
    /// \brief removeRows remove rows in the model (override function)
    /// \param _row row to insert
    /// \param _count count of rows
    /// \param _parent
    /// \return
    ///
    bool removeRows(int _row, int _count, const QModelIndex &_parent) Q_DECL_OVERRIDE;

    ///
    /// \brief setData Sets the role data for the item at index to value. The dataChanged() signal should be emitted if the data was successfully set.
    /// \param _index Index is used to locate data in a data model.
    /// \param _value Value acts like a union for the most common Qt data types. 
    /// \param _role The data in a form suitable for editing in an editor.
    /// \return Returns true if successful; otherwise returns false.
    ///
    bool setData(const QModelIndex &_index, const QVariant &_value, int _role = Qt::EditRole) Q_DECL_OVERRIDE;

    ///
    /// \brief flags The base class implementation returns a combination of flags that enables the item (ItemIsEnabled) and allows it to be selected (ItemIsSelectable).
    /// \param _index Index which the flags are returned for
    /// \return Returns the item flags for the given index.
    ///
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
    /// sort by diferent parameters
    bool static sortByIniFrame(FrameBasedData i,FrameBasedData j);
    bool static sortByEndFrame(FrameBasedData i,FrameBasedData j);
    bool static sortByName(FrameBasedData i,FrameBasedData j);
    bool static sortByCategory(FrameBasedData i,FrameBasedData j);
    bool static sortByLabel(FrameBasedData i,FrameBasedData j);
};

#endif // QFRAMEBASEDTABLEMODEL_H
