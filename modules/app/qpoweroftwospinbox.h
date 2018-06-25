#ifndef QPOWEROFTWOSPINBOX_H
#define QPOWEROFTWOSPINBOX_H

#include <QSpinBox>

class QPowerOfTwoSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    ///
    /// \brief QPowerOfTwoSpinBox Contructor for a spinbox
    /// \param parent parent of the spinbox
    ///
    QPowerOfTwoSpinBox(QWidget* parent = 0);

public slots:
    ///
    /// \brief stepBy Change the number selected in the spinbox.
    /// \param steps number of jumps in the spinbox alway two by two
    ///
    void stepBy(int steps);
};

#endif // QPOWEROFTWOSPINBOX_H
