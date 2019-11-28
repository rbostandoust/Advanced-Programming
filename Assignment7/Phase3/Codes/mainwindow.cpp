#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "addbook.h"
#include "addchapter.h"
#include <QtCore>
#include <QtGui>

using namespace std;

MainWindow::MainWindow(UserInterface* _my_ui, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    curr_user_UI(_my_ui)
{
    ui->setupUi(this);

    editor = new Editor(curr_user_UI);
    string server_query = "List_books";
    server_query += DELIMETER + curr_user_UI->get_username();
    make_book_tree(curr_user_UI->send_then_receive(server_query));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLog_Out_triggered()
{
    Login* w = new Login();
    w->show();
    close();
}

void MainWindow::on_actionNew_Book_triggered()
{
    AddBook* new_book_window = new AddBook(curr_user_UI, this);
    new_book_window->setWindowTitle("New Book");
    new_book_window->show();
}

void MainWindow::make_book_tree(std::string parsed_list){
    ui->books_tree->clear();
    if(parsed_list == ""){
        return;
    }
    vector<string> unparsed_list = split_line(parsed_list, DELIMETER);
    int counter = 0;

    while(unparsed_list.size() != 0){
        string book_name = unparsed_list[0];
        string user_pos = unparsed_list[1];
        string book_state = unparsed_list[2];
        add_root(book_name, user_pos, book_state);
        int num_of_chapters = atoi(unparsed_list[3].c_str());
        for (int i = 0; i < num_of_chapters; ++i)
            add_child(ui->books_tree->topLevelItem(counter), int_to_string(i + 1) + ". " + unparsed_list[i + 4]);
        delete_first_n_block_of_vector(unparsed_list, num_of_chapters + 4);
        counter++;
    }
}

void MainWindow::add_root(std::string title, std::string pos, std::string book_state){
    QTreeWidgetItem* itm = new QTreeWidgetItem(ui->books_tree);
    itm->setText(0, QString::fromStdString(title));
    itm->setText(1, QString::fromStdString(pos));
    itm->setText(2, QString::fromStdString(book_state));
    ui->books_tree->addTopLevelItem(itm);
}

void MainWindow::add_child(QTreeWidgetItem *parent, std::string title){
    QTreeWidgetItem* itm = new QTreeWidgetItem();
    itm->setText(0, QString::fromStdString(title));
    parent->addChild(itm);
}


void MainWindow::on_books_tree_itemSelectionChanged()
{
    QTreeWidgetItem* itm = ui->books_tree->currentItem();
    if(itm->parent() != NULL) // != parent
        itm = itm->parent();
    vector<bool> btns_enablity(7);

    if(itm->text(2).toStdString() == "writing"){
        if(itm->text(1).toStdString() == "owner")
            btns_enablity = {1,1,0,1,1,1,1};
        else if(itm->text(1).toStdString() == "author")
            btns_enablity = {1,1,0,0,0,0,0};
        else
            btns_enablity = {0,0,0,0,0,0,0};
    }

    else if(itm->text(2).toStdString() == "waiting_for_approval"){
        btns_enablity = {0,0,0,0,0,0,0};
    }

    else if(itm->text(2).toStdString() == "published"){
        btns_enablity = {0,1,1,0,0,0,0};
    }

//    for (int var = 0; var < 7; ++var) {
//        cout << btns_enablity[var] << '\t';
//    }

    ui->add->setEnabled(btns_enablity[0]);
    ui->clone->setEnabled(btns_enablity[1]);
    ui->export_html->setEnabled(btns_enablity[2]);
    ui->add_author_btn->setEnabled(btns_enablity[3]);
    ui->remove_author_btn->setEnabled(btns_enablity[4]);
    ui->change_name_btn->setEnabled(btns_enablity[5]);
    ui->publish_btn->setEnabled(btns_enablity[6]);
}

void MainWindow::on_add_clicked()
{
    QTreeWidgetItem* itm = ui->books_tree->currentItem();
    if(itm->parent() != NULL) // != parent
        itm = itm->parent();
    AddChapter* new_chapter_window = new AddChapter(curr_user_UI, this, itm->text(0).toStdString());
    new_chapter_window->show();
}

void MainWindow::on_clone_clicked()
{
    QTreeWidgetItem* itm = ui->books_tree->currentItem();
    if(itm->parent() == NULL){ // it was parent
        QMessageBox my_message;
        my_message.setText("<b><span style=color:red>Cloning Chapter failed:</span></b> First, choose a chapter!");
        my_message.setWindowTitle("Error");
        my_message.exec();
        return;
    }

    string chapter_title = ui->books_tree->currentItem()->text(0).toStdString();
    int chapter_number = chapter_title[0] - '0';

    chapter_title.erase(chapter_title.begin());
    chapter_title.erase(chapter_title.begin());
    chapter_title.erase(chapter_title.begin()); //erasing [number.(space)]

    string book_name = itm->parent()->text(0).toStdString();

    string server_query =  "Clone_chapter";
    server_query += DELIMETER + book_name + DELIMETER + curr_user_UI->get_username() + DELIMETER + int_to_string(chapter_number);
    string server_response = curr_user_UI->send_then_receive(server_query);

    vector<string> parsed_result = split_line(server_response, DELIMETER);
    string player_pos = parsed_result[0];
    parsed_result.erase(parsed_result.begin());
    server_response = make_line(parsed_result);
    editor->add_chapter(book_name, player_pos, server_response);

    ui->editor_menu->addItem(("Chapter: " + chapter_title + " from book: " + book_name).c_str());

    QMessageBox my_message;
    my_message.setText("<b><span style=color:green>Cloning Chapter succeed:</span></b> Chapter has been successfully added to your editor.");
    my_message.setWindowTitle("Successful");
    my_message.exec();
}
