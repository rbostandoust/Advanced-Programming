#include "chapter.h"

using namespace std;

Chapter::Chapter(string _t, vector<string> _l) : title(_t) {
	for (int i = 0; i < _l.size(); ++i)
		lines.push_back(_l[i]);
}

Chapter::~Chapter(){
	for (int i = 0; i < versions.size(); ++i)
		delete versions[i];
	versions.clear();
	// cout << "Chapter destructor called\n";
}


Chapter::Chapter(std::string& unparsed_string){
	vector<string> parsed_string = split_line(unparsed_string, DELIMETER);
	title = parsed_string[0];
	int i;
	for (i = 1; i < parsed_string.size(); i ++)
	{
		if(parsed_string[i] == "*")
			break;
		lines.push_back(parsed_string[i]);
	}
	delete_first_n_block_of_vector(parsed_string, i + 1);
	add_unparsed_versions(parsed_string);
}

void Chapter::add_unparsed_versions(vector<string>& parsed_string){
	int i;
	for (i = 0; i < parsed_string.size(); i++)
	{
		int num_of_commands = atoi(parsed_string[i].c_str());
		Version* temp_v = new Version();
		for (int j = 0; j < 4 * num_of_commands; j += 4, i += 4)
		{
			Command* temp_c = return_correct_command(atoi(parsed_string[i+1].c_str()), parsed_string[i+2], parsed_string[i+3], parsed_string[i+4], this);
			temp_v->add_command(temp_c);
		}
		add_version(temp_v);
	}
}


void Chapter::change_line(int line_number, string value){
	lines[line_number - 1] = value;
}

void Chapter::delete_line(int line_number){
	lines.erase(lines.begin() + line_number - 1);	
}

void Chapter::insert_line(int line_number, string value){
	lines.insert(lines.begin() + line_number - 1, value);
}

string& Chapter::get_line(int line_number){
	if(line_number > 0 && line_number <= lines.size())
		return lines[line_number - 1];
	cout << "\nUnknown index\n\n";
}

string Chapter::to_string(){
	string result = "";
	result += title;
	for (int i = 0; i < lines.size(); ++i)
		result += DELIMETER + lines[i];

	result += DELIMETER ;
	result += "*"; // for separating lines and versions

	for (int i = 0; i < versions.size(); ++i){
		result += DELIMETER + int_to_string(versions[i]->num_of_commands()); // to know size of commands of each version
		result += DELIMETER + versions[i]->to_string();
	}	
	return result;
}

Command* Chapter::return_correct_command(int line_number, string do_value, string undo_value, string type, Chapter* _c){
	if(type == "Update")
		return (new Update(line_number, do_value, undo_value, type, _c));
	if(type == "Insert")
		return (new Insert(line_number, do_value, undo_value, type, _c));
	return (new Delete(line_number, do_value, undo_value, type, _c));
}

int Chapter::num_of_versions(){
	return versions.size();
}
int Chapter::num_of_lines(){
	return lines.size();
}
Version* Chapter::get_versions(int n){
	return versions[n];
}


void Chapter::show_version(int version_number){
	back_to_version(version_number);
	print_lines();
	go_to_last_version(version_number);
}

void Chapter::print_lines(){
	cout << "---------------------------------" << endl;
	for (int i = 0; i < lines.size(); ++i)
		cout << i + 1 << "." << lines[i] << endl;
	cout << "---------------------------------" << endl;
}

void Chapter::back_to_version(int version_number){
	for (int i = num_of_versions() - 1; i >= version_number; --i)
		versions[i]->undo();
}

void Chapter::go_to_last_version(int current_version){
	for (int i = current_version; i < num_of_versions(); ++i)
		versions[i]->apply();
}

void Chapter::add_version(Version* new_version){
	versions.push_back(new_version);
}

void Chapter::apply_new_version(){
	versions.back()->apply();
}

void Chapter::apply_new_versions(int num_of_new_versions){
	for (int i = num_of_new_versions - 1; i >= 0; --i)
		versions[num_of_versions() - i - 1]->apply();
}

void Chapter::return_to_version(int version_number){
	int end = num_of_versions() - 1;
	for (int i = end; i >= version_number; --i){
		versions[i]->undo();
		delete versions[i];
		versions.erase(versions.begin() + i);
	}
}