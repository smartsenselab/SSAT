#ifndef DIALOGSETUP_H
#define DIALOGSETUP_H

#include <QDialog>

namespace Ui {
class DialogSetup;
}

class DialogSetup : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetup(QWidget *parent = 0);
    ~DialogSetup();

private:
    Ui::DialogSetup *ui;
};

#endif // DIALOGSETUP_H
