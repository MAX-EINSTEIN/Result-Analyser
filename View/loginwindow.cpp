#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pb_Login_clicked()
{
    if(ui->le_Password->text()==_password)
    {
        child_Window->setWindowState(Qt::WindowMaximized);
        child_Window->show();
        this->hide();
    }
    else
    {
        QMessageBox::warning(this,"Wrong Password!","You enterd a wrong password!\nPlease try again.");
    }

}

void LoginWindow::setChild_Window(MainView *value)
{
    child_Window = value;
}

void LoginWindow::setPassword(const QString &password)
{
    _password = password;
}
