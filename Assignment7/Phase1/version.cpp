#include "version.h"

using namespace std;

Version::Version(){}

Version::~Version(){
	for (int i = 0; i < commands.size(); ++i)
		delete commands[i];
	commands.clear();
	// cout << "Version destructor called\n";
}

string Version::to_string(){
	string result = "";
	for (int i = 0; i < commands.size(); ++i){
		if(i == 0)
			result += commands[i]->to_string(); 
		else
			result += ',' + commands[i]->to_string();
	}
	return result;
}

void Version::add_command(Command* new_command){
	commands.push_back(new_command);
}

int Version::num_of_commands(){
	return commands.size();
}

void Version::apply(){
	for (int i = 0; i < num_of_commands(); ++i){
		commands[i]->apply_change();
		// cout << "command " << i << " applied\n";
	}
}

void Version::undo(){
	for (int i = num_of_commands() - 1; i >= 0; --i){
		commands[i]->undo_change();
		// cout << "command " << i << " undoed\n";
	}
}