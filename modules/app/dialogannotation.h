#ifndef DIALOGANNOTATION_H
#define DIALOGANNOTATION_H

#include <iostream>
#include <string>
using std::string;

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>

#include "treemodel.h"

namespace Ui {
    class DialogAnnotation;
}

class DialogAnnotation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAnnotation(QWidget *parent = 0);
    ~DialogAnnotation();

    void insertCategory(QTreeWidgetItem *parent, string _name);
    void insertLabel(string _name);
    void removeRow();


private:
    Ui::DialogAnnotation *ui;
    QMultiMap<string, string> *treeContent;

public slots:
    void slot_initializeDialog();

private slots:
    void slot_insertChild();
    bool slot_insertColumn();
    void slot_insertRow();
    bool slot_removeColumn();
    void slot_removeRow();
};

#endif // DIALOGANNOTATION_H
