#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user_interface.h"
#include "editor.h"
#include "utility.h"
#include <vector>
#include <cstdlib>
#include <string>
#include <QTreeWidgetItem>
#include <QTreeWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(UserInterface* _my_ui, QWidget *parent = 0);
    void make_book_tree(std::string parsed_list);
    void add_root(std::string title, std::string pos, std::string book_state);
    void add_child(QTreeWidgetItem *parent, std::string title);
    ~MainWindow();

private slots:
    void on_actionLog_Out_triggered();

    void on_actionNew_Book_triggered();

    void on_add_clicked();

    void on_books_tree_itemSelectionChanged();

    void on_clone_clicked();

private:
    Ui::MainWindow *ui;
    UserInterface* curr_user_UI;
    Editor* editor;
};

#endif // MAINWINDOW_H
