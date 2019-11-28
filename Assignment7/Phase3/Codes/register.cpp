#include "register.h"
#include "ui_register.h"
#include <QMessageBox>

using namespace std;

Register::Register(UserInterface* _my_ui, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register),
    curr_user_UI(_my_ui)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_submit_clicked()
{
    string username = ui->username->text().toStdString();
    string password = ui->password->text().toStdString();
    string r_password = ui->r_password->text().toStdString();
    string server_query = "Register";
    server_query += DELIMETER + username + DELIMETER + password;

    QMessageBox my_message;
    bool error = false;

    if(username == "" || password == "" || r_password == ""){
        my_message.setText("<b><span style=color:red>Log in failed:</span></b> There is an empty input.");
        my_message.setWindowTitle("Error");
        error = true;
    }
    if(password != r_password){
        my_message.setText("<b><span style=color:red>Log in failed:</span></b> The passwords doesn't match.");
        my_message.setWindowTitle("Error");
        error = true;
    }

    string result;
    if(!error)
        result = curr_user_UI->send_then_receive(server_query);

    if(result == "ExistingUser"){
        my_message.setText("<b><span style=color:red>Log in failed:</span></b> There is an existing user with this username.");
        my_message.setWindowTitle("Error");
        error = true;
    }
    ui->password->clear();
    ui->r_password->clear();
    if(!error && result == "Success"){
        my_message.setText("<b><span style=color:green>Registeration was succsessful:</span></b> Now you can login with your account!");
        my_message.setWindowTitle("Succsess");
        this->close();

        Login *l = new Login();
        l->show();
    }
    my_message.exec();
}

void Register::on_pushButton_clicked()
{
    this->close();
    Login *l = new Login();
    l->show();
}
