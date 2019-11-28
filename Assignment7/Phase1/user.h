#ifndef __USER_H__
#define __USER_H__

#include <string>

enum Gender
{
	male , female
};

struct Date
{
	int day;
	int month;
	int year;
};

class User
{
public:
	User(std::string _un, std::string _pw) : username(_un) , password(_pw) {};
	std::string get_username();
	std::string get_password();
	virtual bool is_admin();
	void edit_profile();
protected:
	std::string username;
	std::string password;
	std::string first_name;
	std::string last_name;
	Gender gender;
	Date birthday;
};

#endif