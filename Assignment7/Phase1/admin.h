#ifndef __ADMIN_H__
#define __ADMIN_H__

#include "user.h"

class Admin : public User
{
public:
	Admin(std::string _un, std::string _pw)
		: User(_un, _pw){};
	bool is_admin();
private:
	
};

#endif