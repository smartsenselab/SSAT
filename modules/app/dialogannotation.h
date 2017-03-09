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

private:
    Ui::DialogAnnotation *ui = NULL;

    QAction *enterPressed = NULL;
    QMultiMap<QString, QString> qAttributes;

    QStandardItemModel *qStandardModel = NULL;

    QString selectedCategory;
    QString selectedLabel;

    Core *singleton = NULL;

public:
    explicit DialogAnnotation(QWidget *parent = 0);
    ~DialogAnnotation();

private:
    ///
    /// \brief connectSignalSlots connect button signals to their slots
    ///
    void connectSignalSlots();

    ///
    /// \brief enableWidgets Enable (Insert Cat/Label/Remove) buttons
    /// \param _enable true or false
    ///
    void enableWidgets(const bool _enable);

    ///
    /// \brief updateCoreContent Does nothing
    ///
    void updateCoreContent();

public slots:
    ///
    /// \brief slot_initializeDialog Load information from core and initialize tree
    /// \param _singleton Core
    ///
    void slot_initializeDialog(Core &_singleton);

private slots:
    ///
    /// \brief slot_insertCategoryPressed Insert new Category to the tree
    ///
    void slot_insertCategoryPressed();

    ///
    /// \brief slot_insertLabelPressed Insert new Label to the tree
    ///
    void slot_insertLabelPressed();

    ///
    /// \brief slot_removePressed Remove Category or Label
    ///
    void slot_removePressed();

    ///
    /// \brief slot_accept When Ok is pressed, save all tree changes on core
    ///
    void slot_accept();

    ///
    /// \brief slot_reject When Cancel is pressed, discard all tree changes
    ///
    void slot_reject();

    ///
    /// \brief slot_enterShortcut When Enter key is pressed, save all tree changes on core
    ///
    void slot_enterShortcut();
};

#endif // DIALOGANNOTATION_H
