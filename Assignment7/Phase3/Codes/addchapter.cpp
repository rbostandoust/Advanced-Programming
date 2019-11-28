#include "addchapter.h"
#include "ui_addchapter.h"

using namespace std;

AddChapter::AddChapter(UserInterface* _my_ui, MainWindow* _o, std::string b_n, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddChapter),
    curr_user_UI(_my_ui),
    obj(_o),
    book_name(b_n)
{
    ui->setupUi(this);
    string server_query = "Chapter_number";
    server_query += DELIMETER + book_name;
    num_of_chapters = atoi((curr_user_UI->send_then_receive(server_query)).c_str());

    for (int i = 1; i <= num_of_chapters + 1; ++i)
        ui->chapter_number->addItem(QString::number(i));
    ui->book_name->setText(QString::fromStdString(book_name));
    ui->book_name->setEnabled(false);
}

AddChapter::~AddChapter()
{
    delete ui;
}


void AddChapter::on_submit_clicked()
{
    string chapter_title = ui->chapter_title->text().toStdString();

    string server_query = "Add_chapter";
    server_query += DELIMETER + book_name + DELIMETER + chapter_title + DELIMETER + (ui->chapter_number->currentText().toStdString());

    if(chapter_title == ""){
        show_empty_input_error("Adding Chapter");
        return;
    }

    if(ui->file_radio->isChecked()){
        string address = ui->file_input->text().toStdString();
        vector<string> new_chapter_lines = read_file_content(address);
        if(new_chapter_lines.size() > 0)
            server_query += DELIMETER + make_line(new_chapter_lines);
    }
    else{
        QString plainTextEditContents = ui->typing_input->toPlainText();
        QStringList q_lines = plainTextEditContents.split("\n");
        for(int i = 0; i < q_lines .size(); i++)
            server_query += DELIMETER + q_lines [i].toStdString();
    }

    string result = curr_user_UI->send_then_receive(server_query);
    if(result == "Success"){
        QMessageBox my_message;
        my_message.setText("<b><span style=color:green>Chapter was added succsessfully</span></b>");
        my_message.setWindowTitle("Succsess");
        my_message.exec();
        this->close();

        string server_query = "List_books";
        server_query += DELIMETER + curr_user_UI->get_username();
        obj->make_book_tree(curr_user_UI->send_then_receive(server_query));;
    }
}
