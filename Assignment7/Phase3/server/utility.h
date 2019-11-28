#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "exeption.h"

#define DELIMETER '|'

enum BookState
{
	waiting_for_approval, writing, published
};

void remove_space(std::string& line);
std::vector<std::string> split_line(std::string line, char delimeter);
std::string make_line(std::vector<std::string> parts);
void print_parsed_line(std::string line);
std::vector<std::string> read_file_content(std::string file_name);
bool is_file_exist(std::string file_name);
std::string get_till_end_symbol(std::string end_symbl, char delimeter);
void getline_manual(std::string& line);
void flush_input();
std::string int_to_string(int a);
void delete_first_n_block_of_vector(std::vector<std::string>& vec, int num);
std::string status_to_string(BookState bs);
BookState string_to_status(std::string s);

#endif