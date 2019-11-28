#ifndef __BOOK_H__
#define __BOOK_H__

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "user.h"
#include "chapter.h"
#include "utility.h"

enum BookState
{
	waiting_for_approval, writing, published
};

class Book
{
public:
	Book(std::string name, User* owner, std::vector<User*> authors);
	~Book();
	std::string get_name();
	void set_name(std::string _n);
	std::string get_user_position(User* user);
	std::string get_owner_username();
	BookState get_status(){return state;};
	void set_status(BookState _s){state = _s;};
	std::string get_chapters_title();
	void add_chapter(std::string chapter_name, int chapter_number, std::vector<std::string> server_query);
	void add_chapter(Chapter* new_chapter);
	Chapter* find_chapter_by_name(std::string Chapter_title);
	Chapter* find_chapter_by_number(int Chapter_number);
	int get_author_index(User* author);
	void remove_author(User* author);
	void add_author(User* author);
	std::string export_HTML();
protected:
	std::string name;
	BookState state;
	User* owner;
	std::vector<User*> authors;
	std::vector<Chapter*> chapters;
};

#endif