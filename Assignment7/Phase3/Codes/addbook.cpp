#include "addbook.h"
#include "ui_addbook.h"
#include <QString>
#include <QStringList>
#include <QMessageBox>

using namespace std;

AddBook::AddBook(UserInterface* _my_ui, MainWindow* _o, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddBook),
    curr_user_UI(_my_ui),
    obj(_o)
{
    ui->setupUi(this);
}

AddBook::~AddBook()
{
    delete ui;
}

void AddBook::on_submit_clicked()
{
    string book_name = ui->book_name->text().toStdString();
    QMessageBox my_message;

    if(book_name == ""){
        my_message.setText("<b><span style=color:red>Adding book failed:</span></b> There is an empty input.");
        my_message.setWindowTitle("Error");
        my_message.exec();
        return;
    }

    QString plainTextEditContents = ui->authors_usernane->toPlainText();
    QStringList q_authors = plainTextEditContents.split("\n");

    string server_query = "Add_book";
    server_query += DELIMETER + book_name + DELIMETER + curr_user_UI->get_username();
    for(int i = 0; i < q_authors.size(); i++)
        server_query += DELIMETER + q_authors[i].toStdString();

    string result = curr_user_UI->send_then_receive(server_query);
    if(result == "Existing"){
        my_message.setText("<b><span style=color:red>Adding book failed:</span></b> There is an existing book with this name!");
        my_message.setWindowTitle("Error");
    }
    else if(result != "Success"){
        my_message.setText(("<b><span style=color:red>Adding book failed:</span></b> "+ result).c_str());
        my_message.setWindowTitle("Error");
    }
    else{
        my_message.setText("<b><span style=color:green>Adding book was succsessful</span></b>: Now you can add chapter to it.");
        my_message.setWindowTitle("Succsess");
        this->close();

        string server_query = "List_books";
        server_query += DELIMETER + curr_user_UI->get_username();
        obj->make_book_tree(curr_user_UI->send_then_receive(server_query));;
    }
    my_message.exec();
}
