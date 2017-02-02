#ifndef DIALOGFRAMEBASED_H
#define DIALOGFRAMEBASED_H

#include <cmath>
#include <iostream>

#include <QDialog>
#include <QtCore>
#include <QtGui>

#include "core.h"
#include "framebaseddata.h"

namespace Ui
{
    class DialogFrameBased;
}

class DialogFrameBased : public QDialog
{
    Q_OBJECT

private:

    Ui::DialogFrameBased *ui;

    int frameId, indexId, totalFrames;
    mode manipulation;
    Core *singleton = NULL;

    QStringListModel *categoryModel = NULL;
    QStringListModel *labelModel = NULL;

public:
    explicit DialogFrameBased(QWidget *parent = 0);
    ///
    /// \brief getIniFrameValue return the Ini Frame value
    ///
    int getIniFrameValue();
    ///
    /// \brief getEndFrameValue return the End Frame value
    ///
    int getEndFrameValue();
    ///
    /// \brief getInfoValue return the Info string
    ///
    QString getInfoValue();

private:
    ///
    /// \brief connectSignalSlots Connect button signals
    ///
    void connectSignalSlots();
    ///
    /// \brief initializeComboboxes Load all categories and labels from Core and populate the ComboBoxes
    ///
    void initializeComboboxes();
    ///
    /// \brief enableDisableButtonBox Enable Ok/Cancel button and set FinalFrame equals to IniFrame
    ///
    void enableDisableButtonBox();

public slots:
    ///
    /// \brief slot_initializeDialog Disable buttons and initialize variables
    /// \param _singleton Core
    /// \param _frameId actual frame
    ///
    void slot_initializeDialog(Core &_singleton, const int _frameId);
    ///
    /// \brief slot_initializeDialog Initialize the FrameBased variables with the value
    ///        of the previous item inserted in table
    /// \param _singleton Core
    /// \param _index index of the row selected(row to change the value)
    ///
    void slot_initializeDialog(Core &_singleton, const QModelIndex _index);
    ///
    /// \brief slot_comboBoxCategoryActivated Load all labels of the current category selected
    /// \param _text Current Category
    ///
    void slot_comboBoxCategoryActivated(const QString &_text);
    ///
    /// \brief slot_rewindButtonPressed Change the FinalFrame value to the new frameId
    ///
    void slot_rewindButtonPressed();
    ///
    /// \brief slot_backButtonPressed Change the FinalFrame value to the new frameId
    ///
    void slot_backButtonPressed();
    ///
    /// \brief slot_forwardButtonPressed Change the FinalFrame value to the new frameId
    ///
    void slot_forwardButtonPressed();
    ///
    /// \brief slot_fastfButtonPressed Change the FinalFrame value to the new frameId
    ///
    void slot_fastfButtonPressed();
    ///
    /// \brief slot_buttonBoxAccepted update core with FrameBased values
    ///
    void slot_buttonBoxAccepted();
    ///
    /// \brief slot_buttonBoxRejected Discard all FrameBased values
    ///
    void slot_buttonBoxRejected();
    ///
    /// \brief slot_spinBoxValueChanged Enable SpinBoxButton and set the minimum values
    ///
    void slot_spinBoxValueChanged();
    ///
    /// \brief slot_lineEditInfoChanged ?Chama a mesma funçao que o spinboxvalue?
    ///
    void slot_lineEditInfoChanged();

signals:
    ///
    /// \brief signal_rewindButtonPressed Signal to call Slot_rewind
    ///
    void signal_rewindButtonPressed();
    ///
    /// \brief signal_backButtonPressed Signal to call Slot_back
    ///
    void signal_backButtonPressed();
    ///
    /// \brief signal_forwardButtonPressed Signal to call Slot_foward
    ///
    void signal_forwardButtonPressed();
    ///
    /// \brief signal_fastfButtonPressed signal to call Slot_fastf
    ///
    void signal_fastfButtonPressed();
    ///
    /// \brief signal_buttonBoxAccepted Signal to call buttonBoxAccpeted
    ///
    void signal_buttonBoxAccepted();

    ///
    /// \brief signal_frameBasedInsertAccepted Signal emited when a new data will be inserted
    /// \param _data New FrameBased value to be inserted
    ///
    void signal_frameBasedInsertAccepted(const FrameBasedData _data);
    ///
    /// \brief signal_frameBasedAlterAccepted Signal emited when a old data values will be changed
    /// \param _data FrameBased Value to be changed
    /// \param _index Row index
    ///
    void signal_frameBasedAlterAccepted(const FrameBasedData _data, const int _index);
    ///
    /// \brief signal_frameBasedRejected ?
    ///
    void signal_frameBasedRejected();
};

#endif // DIALOGFRAMEBASED_H
