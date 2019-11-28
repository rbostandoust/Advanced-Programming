#include "command.h"

using namespace std;

std::string Command::to_string(){
	return (int_to_string(line_number) + ',' + do_value + ',' + undo_value + ',' + type);
}


void Update::apply_change(){
	my_chapter->change_line(line_number, do_value);
}
void Update::undo_change(){
	my_chapter->change_line(line_number, undo_value);
}


void Delete::apply_change(){
	my_chapter->delete_line(line_number);
}
void Delete::undo_change(){
	my_chapter->insert_line(line_number, undo_value);
}

void Insert::apply_change(){
	my_chapter->insert_line(line_number, do_value);
}
void Insert::undo_change(){
	my_chapter->delete_line(line_number);
}