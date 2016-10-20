#ifndef DIALOGANNOTATION_H
#define DIALOGANNOTATION_H

#include <iostream>
#include <string>
using std::string;

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QTreeWidget>

namespace Ui {
    class DialogAnnotation;
}

class DialogAnnotation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAnnotation(QWidget *parent = 0);
    ~DialogAnnotation();

    void insertChild(QTreeWidgetItem *parent, string _name);
    void insertRow(string _name);
    void removeRow();


private:
    Ui::DialogAnnotation *ui;

//public slots:
//    void slot_initializeDialog();
};

#endif // DIALOGANNOTATION_H
