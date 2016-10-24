#ifndef QMULTIMAPMODEL_H
#define QMULTIMAPMODEL_H

#include <QAbstractTableModel>
#include <QMap>

class QMultiMapModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    QMultiMapModel();

    explicit QMultiMapModel(QObject *_parent = 0);

    int rowCount(const QModelIndex &_parent = QModelIndex()) const;
    int columnCount(const QModelIndex &_parent = QModelIndex()) const;

    QVariant data(const QModelIndex &_index, int _role = Qt::DisplayRole) const;

    inline void setMap(QMultiMap<QString, QString> *_container)
    {
        this->container = _container;
    }

private:
    QMultiMap<QString, QString> *container;
};

#endif // QMULTIMAPMODEL_H
