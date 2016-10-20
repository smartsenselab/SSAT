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
    void updateActions();


private:
    Ui::DialogAnnotation *ui;
    QMultiMap<string, string> *treeContent;

public slots:
    void slot_initializeDialog();

private slots:
    void slot_insertCategoryPressed();
    void slot_insertLabelPressed();
    void slot_removeRowPressed();
};

#endif // DIALOGANNOTATION_H
