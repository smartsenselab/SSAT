#include "treemodelcompleter.h"
#include <QStringList>

TreeModelCompleter::TreeModelCompleter(QObject *parent)
    : QCompleter(parent)
{
    this->setCaseSensitivity(Qt::CaseInsensitive);
    this->setSeparator(QLatin1String("."));
}

TreeModelCompleter::TreeModelCompleter(QAbstractItemModel *model, QObject *parent)
    : QCompleter(model, parent)
{
}

void TreeModelCompleter::setSeparator(const QString &separator)
{
    this->sep = separator;
}

QString TreeModelCompleter::separator() const
{
    return this->sep;
}

QStringList TreeModelCompleter::splitPath(const QString &path) const
{
    if (this->sep.isNull()) {
        return QCompleter::splitPath(path);
    }

    return path.split(this->sep);
}

QString TreeModelCompleter::pathFromIndex(const QModelIndex &index) const
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
