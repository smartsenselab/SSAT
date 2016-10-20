#ifndef DIALOGANNOTATION_H
#define DIALOGANNOTATION_H

#include <QDialog>

namespace Ui {
    class DialogAnnotation;
}

class DialogAnnotation : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAnnotation(QWidget *parent = 0);
    ~DialogAnnotation();

private:
    Ui::DialogAnnotation *ui;
};

#endif // DIALOGANNOTATION_H
