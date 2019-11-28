#ifndef __CHAPTER_H__
#define __CHAPTER_H__

#include <vector>
#include <cstdlib>
#include <string>
#include "version.h"
#include "utility.h"
#include "command.h"

class Version;
class Command;

class Chapter
{
public:
	Chapter(std::string _t, std::vector<std::string> lines);
	Chapter(std::string& unparsed_string);
	~Chapter();
	void change_line(int line_number, std::string value);
	void delete_line(int line_number);
	void insert_line(int line_number, std::string value);
	std::string& get_line(int line_number);
	std::string get_title(){ return title; };
	std::string to_string();
	int num_of_versions();
	int num_of_lines();
	Version* get_versions(int n);
	Command* return_correct_command(int line_number, std::string do_value, std::string undo_value, std::string type, Chapter* _c);
	void show_version(int version_number);
	void print_lines();
	void back_to_version(int version_number);
	void go_to_last_version(int current_version);
	void add_version(Version*);
	void apply_new_version();
	void apply_new_versions(int num_of_new_versions);
	void add_unparsed_versions(std::vector<std::string>& queries);
	void return_to_version(int version_number);
private:
	std::string title;
	std::vector<std::string> lines;	
	std::vector<Version*> versions;

};

#endif