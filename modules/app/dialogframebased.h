#ifndef DIALOGFRAMEBASED_H
#define DIALOGFRAMEBASED_H

#include <QDialog>

namespace Ui {
    class DialogFrameBased;
}

class DialogFrameBased : public QDialog
{
    Q_OBJECT

public:
    explicit DialogFrameBased(QWidget *parent = 0);
    ~DialogFrameBased();

private:
    Ui::DialogFrameBased *ui;
};

#endif // DIALOGFRAMEBASED_H
