#include "utility.h"

using namespace std;

void remove_space(string& line){
	for (int i = 0; i < line.length(); ++i)
	{
		if(line[i] == ' '){
			line.erase(line.begin() + i);
			i--;
		}
	}
}

vector<string> split_line(string line, char delimeter){
	int i = 0;
	vector<string> result;
	while(i < line.size()){
		if(line[i] == delimeter){
			// if(i != 0)
			result.push_back(line.substr(0, i));
			if(i + 1 != line.size()){
				line = line.substr(i + 1);
				i = 0;			
			}
			else
				line.erase(line.begin() + i);
		}
		else
			i++;
	}
	if(line != "|" || line != "")
		result.push_back(line);
	return result;
}

string make_line(vector<string> parts){
	string result = "";
	for (int i = 0; i < parts.size(); ++i){
		result += parts[i];
		if(i != parts.size() - 1)
			result += DELIMETER;
	}
	return result;
}

void print_parsed_line(std::string line){
	vector<string> result = split_line(line, DELIMETER);
	for (int i = 0; i < result.size(); ++i)
		cout << result[i] << endl;
}

vector<string> read_file_content(string file_name){
	file_name = "../new_chapter_input/" + file_name;
//	if(!is_file_exist(file_name))
//		throw Exeption("NoFileExist");
	ifstream in(file_name.c_str());
	vector<string> lines;
	string line;
	while(!in.eof()){
		getline(in, line);
		if(line != "" && line != "\n")
			lines.push_back(line);	
	}
	return lines;
}

bool is_file_exist(string file_name){
	ifstream infile(file_name.c_str());
    return !(infile);
}

string get_till_end_symbol(string end_symbl, char delimeter){
	string result = "", line = "";
	while(line != end_symbl){
		getline(cin, line);
		if(line == "" || line == end_symbl)
			continue;
		result += delimeter + line ;
	}
	return result;
}

void getline_manual(string& line){
	line = "";
	while(line == "" || line == "\n")
		getline(cin, line);
}

void flush_input(){
  int ch;
  while ((ch = cin.get()) != '\n' && ch != EOF);
}

string int_to_string(int a){
  string s;
  stringstream out;
  out << a;
  return out.str();
}

void delete_first_n_block_of_vector(std::vector<std::string>& vec, int num){
	for (int i = 0; i < num; ++i)
		vec.erase(vec.begin());
}

void show_empty_input_error(std::string title){
    QMessageBox my_message;
    my_message.setText(("<b><span style=color:red>" + title +" failed:</span></b> There is an empty input.").c_str());
    my_message.setWindowTitle("Error");
    my_message.exec();
    return;
}

std::string status_to_string(BookState bs){
    if(bs == waiting_for_approval)
        return "waiting_for_approval";
    if(bs == writing)
        return "writing";
    return "published";
}

BookState string_to_status(std::string s){
    if(s == "waiting_for_approval")
        return waiting_for_approval;
    if(s == "writing")
        return writing;
    return published;
}
