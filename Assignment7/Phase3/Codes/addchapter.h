#ifndef ADDCHAPTER_H
#define ADDCHAPTER_H

#include <QWidget>
#include "user_interface.h"
#include "mainwindow.h"
#include <string>
#include <cstdlib>
#include <QString>
#include "utility.h"

namespace Ui {
class AddChapter;
}

class AddChapter : public QWidget
{
    Q_OBJECT

public:
    explicit AddChapter(UserInterface* _my_ui, MainWindow* _o, std::string b_n, QWidget *parent = 0);
    ~AddChapter();

private slots:
    void on_submit_clicked();

private:
    Ui::AddChapter *ui;
    UserInterface* curr_user_UI;
    MainWindow* obj;
    std::string book_name;
    int num_of_chapters;
};

#endif // ADDCHAPTER_H
