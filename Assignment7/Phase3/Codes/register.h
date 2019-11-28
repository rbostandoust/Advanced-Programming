#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <string>
#include "user_interface.h"
#include "login.h"

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(UserInterface* _my_ui, QWidget *parent = 0);
    ~Register();

private slots:
    void on_submit_clicked();

    void on_pushButton_clicked();

private:
    Ui::Register *ui;
    UserInterface* curr_user_UI;
};

#endif // REGISTER_H
