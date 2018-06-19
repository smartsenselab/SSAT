#include "qpoweroftwospinbox.h"

QPowerOfTwoSpinBox::QPowerOfTwoSpinBox(QWidget* parent) : QSpinBox(parent)
{
    this->setMinimum(1);
    this->setMaximum(128);
    QSpinBox::setMaximum(128);
}

void QPowerOfTwoSpinBox::stepBy(int steps)
{
    if(steps == 1)
    {
        if (this->value() < 10)
        {
            this->setValue(this->value() + 1);
        }
        else
        {
            this->setValue(this->value() + 10);
        }
    }
    else if(steps == -1)
    {
        if (this->value() <= 10)
        {
            this->setValue(this->value() - 1);
        }
        else
        {
            this->setValue(this->value() - 10);
        }
    }
    else
    {
        QSpinBox::stepBy(steps);
    }
}
