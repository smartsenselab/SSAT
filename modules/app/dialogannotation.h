#ifndef DIALOGANNOTATION_H
#define DIALOGANNOTATION_H

#include <iostream>
#include <string>
#include <map>
using std::string;
using std::multimap;

#include <QDialog>
#include <QModelIndex>
#include <QtCore>
#include <QtGui>
#include <QStandardItemModel>

#include "core.h"

namespace Ui
{
    class DialogAnnotation;
}

class DialogAnnotation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAnnotation(QWidget *parent = 0);
    ~DialogAnnotation();

private:
    void connectSignalSlots();
    void enableWidgets(const bool _enable);
    void updateCoreContent();

private:
    Ui::DialogAnnotation *ui;
    QMultiMap<QString, QString> qAttributes;

    QStandardItemModel *qStandardModel;

    QString selectedCategory;
    QString selectedLabel;

    Core *singleton = NULL;

public slots:
    void slot_initializeDialog(Core &_singleton);

private slots:
    void slot_insertCategoryPressed();
    void slot_insertLabelPressed();
    void slot_removePressed();

    void slot_accept();
    void slot_reject();
};

#endif // DIALOGANNOTATION_H
