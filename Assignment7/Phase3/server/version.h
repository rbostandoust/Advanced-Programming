#ifndef __VERSION_H__
#define __VERSION_H__

#include <vector>
#include <string>
#include <iostream>
#include "utility.h"
#include "command.h"

class Command;

class Version
{
public:
	Version();
	~Version();
	std::string to_string();
	void add_command(Command* new_command);
	int num_of_commands();
	void apply();
	void undo();
	void show_commands();
private:
	std::vector<Command*> commands;	
};

#endif