#include "user.h"

std::string User::get_username(){
	return username;
}

std::string User::get_password(){
	return password;
}

bool User::is_admin(){
	return false;
}
