#ifndef __MY_SERVER_H__
#define __MY_SERVER_H__

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

#include "repository.h"
#include "user.h"
#include "admin.h"
#include "utility.h"

class MyServer
{
public:
	MyServer();
	std::string recieve(std::string command);
	std::string add_user(std::vector<std::string>& queries);
	User* find_user(std::string username);
	std::string log_in(std::vector<std::string>& queries);
	std::string add_book(std::vector<std::string>& queries);
	std::string add_chapter(std::vector<std::string>& queries);
	std::string get_chapter(std::vector<std::string>& queries);
	std::string get_chapter_by_title(std::vector<std::string>& queries);
	std::string Update_chapter(std::vector<std::string>& queries);
private:
	Repository* my_rep;
	std::vector<User*> users;
	Admin* admin;
};

#endif