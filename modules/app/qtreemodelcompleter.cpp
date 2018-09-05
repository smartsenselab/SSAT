#include "qtreemodelcompleter.h"
#include <QStringList>

QTreeModelCompleter::QTreeModelCompleter(QObject *parent)
    : QCompleter(parent)
{
    this->setCaseSensitivity(Qt::CaseInsensitive);
    this->setSeparator(QLatin1String("->"));
}

QTreeModelCompleter::QTreeModelCompleter(QAbstractItemModel *model, QObject *parent)
    : QCompleter(model, parent)
{
}

void QTreeModelCompleter::setSeparator(const QString &separator)
{
    this->sep = separator;
}

QString QTreeModelCompleter::separator() const
{
    return this->sep;
}

QStringList QTreeModelCompleter::splitPath(const QString &path) const
{
    if (this->sep.isNull()) {
        return QCompleter::splitPath(path);
    }

    return path.split(this->sep);
}

QString QTreeModelCompleter::pathFromIndex(const QModelIndex &index) const
{
    if (this->sep.isNull()) {
        return QCompleter::pathFromIndex(index);
    }

    // navigate up and accumulate data
    QStringList dataList;
    for (QModelIndex i = index; i.isValid(); i = i.parent())
    {
        dataList.prepend(model()->data(i, completionRole()).toString());
    }

    return dataList.join(this->sep);
}
