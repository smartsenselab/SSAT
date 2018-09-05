#ifndef TREEMODELCOMPLETER_H
#define TREEMODELCOMPLETER_H

#include <QCompleter>

class QTreeModelCompleter : public QCompleter
{    
    Q_OBJECT
    Q_PROPERTY(QString separator READ separator WRITE setSeparator)

public:
    explicit QTreeModelCompleter(QObject *parent = 0);
    explicit QTreeModelCompleter(QAbstractItemModel *model, QObject *parent = 0);

    QString separator() const;
public slots:
    void setSeparator(const QString &separator);

protected:
    QStringList splitPath(const QString &path) const override;
    QString pathFromIndex(const QModelIndex &index) const override;

private:
    QString sep;
};

#endif // TREEMODELCOMPLETER_H
