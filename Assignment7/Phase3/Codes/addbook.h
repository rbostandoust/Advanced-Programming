#ifndef ADDBOOK_H
#define ADDBOOK_H

#include <QWidget>
#include "user_interface.h"
#include "mainwindow.h"
#include <string>

namespace Ui {
class AddBook;
}

class AddBook : public QWidget
{
    Q_OBJECT

public:
    explicit AddBook(UserInterface* _my_ui, MainWindow* _o, QWidget *parent = 0);
    ~AddBook();

private slots:
    void on_submit_clicked();

private:
    Ui::AddBook *ui;
    UserInterface* curr_user_UI;
    MainWindow* obj;
};

#endif // ADDBOOK_H
