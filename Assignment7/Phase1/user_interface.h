#ifndef __USER_MACHINE_H__
#define __USER_MACHINE_H__

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "user.h"
#include "book.h"
#include "my_server.h"
#include "utility.h"
#include "editor.h"

#define END_SYMBOL "#"

class Editor;

class UserInterface
{
public:
	UserInterface(MyServer* _s);
	//~UserMachine();
	void handle();
	bool logged_in();
	void register_new_user();
	bool is_log_in_command_ok(std::string command);
	void log_out_user();
	void add_book();
	void get_books_list();
	void select_book();
	void add_chapter(std::string book_name, int num_of_chapters);
	void get_content_from_file(std::vector<std::string>& new_chapter_lines);
	std::string get_content_from_terminal();
	void clone_chapter(std::string book_name, int num_of_chapters);
	int get_chapter_number(int num_of_chapters, bool for_new_chapter = false);
	std::string get_username(){return username;};
	void accept_books_system_run();
	
	void add_author(std::string book_name);
	void remove_author(std::string book_name);
	void change_book_name(std::string pre_book_name);

	std::string send(std::string);
	void show_introductoin(std::string _u);
	void show_log_in_introduction();
	void show_book_introduction(bool show_last, std::string book_status, std::string player_post);
	void show_add_content_to_new_chapter_introduction();
private:
	std::string username;
	Editor* editor;
	MyServer* server;
};


#endif