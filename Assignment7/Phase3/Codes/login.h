#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

#include <QApplication>
#include <QString>
#include <cstdlib>
#include <iostream>
#include <string>
#include "client_socket.h"
#include "user_interface.h"
#include "utility.h"

#define END_SYMBOL "#"
#define ADMIN_USERNAME "admin"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_login_btn_clicked();

    void on_register_btn_clicked();

private:
    Ui::Login *ui;
    UserInterface* curr_user_UI;
};

#endif // LOGIN_H
