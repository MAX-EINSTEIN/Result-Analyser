#ifndef CLASSES_H
#define CLASSES_H

#include <QDialog>

namespace Ui {
class Classes;
}

class Classes : public QDialog
{
    Q_OBJECT

public:
    explicit Classes(QWidget *parent = nullptr);
    ~Classes();

    void setSections(int sections);

private:
    Ui::Classes *ui;
    int _sections;
};

#endif // CLASSES_H
