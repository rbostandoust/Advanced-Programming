#ifndef __YARD_H__
#define __YARD_H__

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

#include "child.h"

#define BLOCK 'b'
#define WHITE_SPACE 'w'

class Yard
{
public:
	Yard();
	void declare_map();
	void print_map();
	bool is_in_wall(Point pos);
private:
	std::vector<std::string> map;
};

#endif