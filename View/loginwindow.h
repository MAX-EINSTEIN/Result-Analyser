#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "View/mainview.h"
#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    void setPassword(const QString &password);

    void setChild_Window(MainView *value);

private slots:
    void on_pb_Login_clicked();

private:
    QString _password;
    Ui::LoginWindow *ui;
    MainView *child_Window;
};

#endif // LOGINWINDOW_H
