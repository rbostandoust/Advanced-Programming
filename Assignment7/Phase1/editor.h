#ifndef __EDITOR_H__
#define __EDITOR_H__

#include <vector>
#include <string>
#include <iostream>

#include "user_interface.h"
#include "chapter.h"
#include "version.h"
#include "utility.h"

#define QUIT 0
#define NEW_VERSION 1
#define LOOKING_VERSIONS 2
#define RETURN_PREVIOUS 3
#define PUSH 4
#define UPDATE 5
#define BACK_TO_MAIN_MENU 6 
#define SUBMIT 7
#define DELETE 8

class UserInterface;

class Editor{
public:
	Editor(UserInterface* _u_UI) : userUI(_u_UI){};
	~Editor();
	void add_chapter(std::string _b_n, std::string _u_p, std::string& unparsed_string);
	void run();

	int num_of_chapters(){return edit_chapter.size();};
	int get_chapter_number();
	int get_version_number(int chapter_number);
	void show_version(int chapter_number);
	void add_new_version(int chapter_number);
	void edit_new_version(int chapter_number);
	bool is_command_ok(std::vector<std::string> result, int num_of_lines);
	void push_to_server(int chapter_number);
	void return_to_previous_version(int chapter_number);
	void add_new_version_to_chapter(int chapter_number);
	void delete_new_version(int chapter_number);
	void reload_chapter(int chapter_number);
	void send_return_to_previous_version_to_server(int chapter_number);
	bool has_permission(int chapter_number);

	void show_introduction(bool started_new_version);
	void show_chapters_list();
	void show_commands_structure();
private:
	std::vector<Chapter*> edit_chapter;
	std::vector<Version*> new_version;
	std::vector<std::string> book_name;
	std::vector<int> num_of_versions_before_editing;
	std::vector<bool> started_new_version;
	std::vector<std::string> user_position;
	std::vector<int> version_to_return;
	UserInterface* userUI;
};

#endif