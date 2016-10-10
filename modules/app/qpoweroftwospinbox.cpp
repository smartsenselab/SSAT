#include "qpoweroftwospinbox.h"

QPowerOfTwoSpinBox::QPowerOfTwoSpinBox(QWidget* parent) : QSpinBox(parent)
{

}

void QPowerOfTwoSpinBox::stepBy(int steps)
{
    if(steps == 1)
    {
        this->setValue(this->value()*2);
    }
    else if(steps == -1)
    {
        this->setValue(this->value()/2);
    }
    else
    {
        QSpinBox::stepBy(steps);
    }
}
