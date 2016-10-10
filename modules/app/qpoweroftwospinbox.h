#ifndef QPOWEROFTWOSPINBOX_H
#define QPOWEROFTWOSPINBOX_H

#include <QSpinBox>

class QPowerOfTwoSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    QPowerOfTwoSpinBox(QWidget* parent = 0);

public slots:
    void stepBy(int steps);
};

#endif // QPOWEROFTWOSPINBOX_H
