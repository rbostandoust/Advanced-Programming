#ifndef __MY_SERVER_H__
#define __MY_SERVER_H__

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "repository.h"
#include "server.h"
#include "user.h"
#include "utility.h"

class MyServer : public Server
{
public:
	MyServer(int port);
	~MyServer();
	std::string proccess(std::string command);
	std::string add_user(std::vector<std::string>& queries);
	User* find_user(std::string username);
	std::string log_in(std::vector<std::string>& queries);
	std::string add_book(std::vector<std::string>& queries);
	std::string add_chapter(std::vector<std::string>& queries);
	std::string get_chapter(std::vector<std::string>& queries);
	std::string get_chapter_by_title(std::vector<std::string>& queries);
	std::string Update_chapter(std::vector<std::string>& queries);

	void on_standard_input(std::string line);
	void on_new_connection(int identifier);
	void on_new_message(int identifier, std::string message);
	void on_terminated_connection(int identifier);
private:
	Repository* my_rep;
	std::vector<User*> users;
	User* admin;
};

#endif