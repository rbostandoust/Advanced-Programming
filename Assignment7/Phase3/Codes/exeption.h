#ifndef __EXEPTION_H__
#define __EXEPTION_H__

#include <string>

class Exeption
{
public:
	Exeption(std::string _m) : massage(_m) {};
	std::string get_massage(){return massage;};
private:
	std::string massage;	
};



#endif