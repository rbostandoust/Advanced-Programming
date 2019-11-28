#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__

#include <vector>
#include <iostream>

#include "user.h"
#include "admin.h"
#include "book.h"
#include "exeption.h"

class Repository
{
public:
	Repository();
	//~Repository();
	void add_book(std::string name, User* owner, std::vector<User*> authors);
	void delete_book(std::string name);
	std::string list_books(User* user);
	std::string get_book_chapters_title(std::string book_name, User* user);
	Book* find_book(std::string book_name);
	bool is_existing(std::string book_name);
	std::string get_wating_for_approval_books();
	bool is_first_book(User* user);
private:
	std::vector<Book*> books;
};

#endif