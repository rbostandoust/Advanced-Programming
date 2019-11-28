#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "register.h"
#include "mainwindow.h"

using namespace std;

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    curr_user_UI = new UserInterface("127.0.0.1", 8080);
    cout << "# connection established" << endl;
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_btn_clicked()
{
    string username = ui->username->text().toStdString();
    string password = ui->password->text().toStdString();

    string server_query = "Log_in";
    server_query += DELIMETER + username + DELIMETER + password;

    QMessageBox my_message;
    bool error = false;

    if(username == "" || password == ""){
        my_message.setText("<b><span style=color:red>Log in failed:</span></b> There is an empty input.");
        my_message.setWindowTitle("Error");
        error = true;
    }

    string result;
    if(!error)
        result = curr_user_UI->send_then_receive(server_query);

    if(!error && result == ""){
        my_message.setText("<b><span style=color:red>Log in failed:</span></b> Username or password is incorect.");
        my_message.setWindowTitle("Error");
        error = true;
    }
    ui->password->clear();
    if(!error){
        my_message.setText(("<b><span style=color:green>Log in succsessfully:</span></b> " + result + " wellcome!").c_str());
        my_message.setWindowTitle("Succsess");
        this->close();
        curr_user_UI->set_username(result);
        MainWindow *main_window = new MainWindow(curr_user_UI);
        main_window->setWindowTitle((result + " Main Window").c_str());
        main_window->show();
    }
    my_message.exec();
}

void Login::on_register_btn_clicked()
{
    Register *register_window = new Register(curr_user_UI);
    register_window->setWindowTitle("Registration");
    register_window->show();
    close();
}
