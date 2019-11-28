#include "editor.h"

using namespace std;

Editor::~Editor(){
	for (int i = 0; i < edit_chapter.size(); ++i)
	{
		delete edit_chapter[i];
		delete new_version[i];
	}
	edit_chapter.clear();
	new_version.clear();
}

void Editor::add_chapter (string _b_n, string _u_p, string& unparsed_string){
	book_name.push_back(_b_n);
	user_position.push_back(_u_p);
	edit_chapter.push_back(new Chapter(unparsed_string));
	num_of_versions_before_editing.push_back(edit_chapter.back()->num_of_versions());
	started_new_version.push_back(false);
	version_to_return.push_back(-1);
	new_version.push_back(new Version());
}

void Editor::run(){
	if(num_of_chapters() == 0){
		cout << "No chapter has been added yet!! Please first of all add chapters(Select_book -> Edit_chapter)\n";
		return;
	}
	int selected_chapter = -1;
	while(true){
		while(selected_chapter <= 0 || selected_chapter > num_of_chapters() + 1){
			show_chapters_list();		
			selected_chapter = get_chapter_number();
			if(selected_chapter == QUIT)
				return;
		}
		bool end_loop = false;
		while(!end_loop){
			show_introduction(started_new_version[selected_chapter - 1]);
			int command;
			cin >> command;
			flush_input();
			switch(command){
				case NEW_VERSION:
					if(started_new_version[selected_chapter - 1])
						edit_new_version(selected_chapter);
					else
						add_new_version(selected_chapter);
					break;
				case LOOKING_VERSIONS:
					show_version(selected_chapter);
					break;
				case RETURN_PREVIOUS:
					return_to_previous_version(selected_chapter);
					break;
				case PUSH:
					push_to_server(selected_chapter);
					break;
				case UPDATE:
					reload_chapter(selected_chapter);
					break;
				case BACK_TO_MAIN_MENU:
					end_loop = true;
					break;
				case SUBMIT:
					if(started_new_version[selected_chapter - 1]){
						add_new_version_to_chapter(selected_chapter);
						break;
					}
				case DELETE:
					if(started_new_version[selected_chapter - 1]){
						delete_new_version(selected_chapter);
						break;
					}
				default:
					cout << "Wrong input\n";
			}
		}
		selected_chapter = -1;
	}
}

int Editor::get_chapter_number(){
	cout << "Enter a number between 1 and " << num_of_chapters() << " (Enter 0 to quit from editor):\n";
	int i;
	cin >> i;
	flush_input();
	if(i < 0 || i > num_of_chapters() + 1)
		cout << "The number you entered is not in range. please try again..." << endl;
	return i;
}

int Editor::get_version_number(int chapter_number){
	//cout << "We have " << edit_chapter[chapter_number - 1]->num_of_versions() << " versions in this chapter";
	cout << "Enter a number between 0 and " << edit_chapter[chapter_number - 1]->num_of_versions() << "(0 for base chapter):\n";
	int i;
	while(true){
		cin >> i;
		flush_input();
		if(i < 0 || i > edit_chapter[chapter_number - 1]->num_of_versions() + 1){
			cout << "The number you entered is not in range. please try again..." << endl;
			continue;
		}
		return i;
	}
}

void Editor::show_version(int chapter_number){
	int version_number = get_version_number(chapter_number);
	edit_chapter[chapter_number - 1]->show_version(version_number);
}

void Editor::edit_new_version(int chapter_number){
	if(!has_permission(chapter_number))
		return;
	edit_chapter[chapter_number - 1]->show_version(edit_chapter[chapter_number - 1]->num_of_versions());
	show_commands_structure();
	bool end = false;
	while(!end){
		string command_line;
		getline_manual(command_line);
		if(command_line == "Quit"){
			end = true;
			continue;
		}
		vector<string> result = split_line(command_line, ',');
		if(result.size() >= 2){
			remove_space(result[0]);
			remove_space(result[1]);
		}
		if(!is_command_ok(result, edit_chapter[chapter_number - 1]->num_of_lines())){
			cout << "Wrong input" <<endl;
			continue;
		}
		int line_number = atoi(result[1].c_str());
		Command* new_command;
		if(result[0] == "Delete")
			new_command = new Delete(line_number, "#", edit_chapter[chapter_number - 1]->get_line(line_number), "Delete", edit_chapter[chapter_number - 1]);
		else{
			result[2].erase(result[2].begin());
			result[2].erase(result[2].end() - 1);
			if(result[0] == "Insert")
				new_command = new Insert(line_number, result[2], "#", "Insert", edit_chapter[chapter_number - 1]);
			else if(result[0] == "Update")
				new_command = new Update(line_number, result[2], edit_chapter[chapter_number - 1]->get_line(line_number), "Update", edit_chapter[chapter_number - 1]);
		}
		new_version[chapter_number - 1]->add_command(new_command);
		new_command->apply_change();
		edit_chapter[chapter_number - 1]->show_version(edit_chapter[chapter_number - 1]->num_of_versions());
	}
}

void Editor::add_new_version(int chapter_number){
	if(!has_permission(chapter_number))
		return;
	started_new_version[chapter_number - 1] = true;
	cout << "New version has been added successfully.\n";
	edit_new_version(chapter_number);
}

bool Editor::is_command_ok(vector<string> result, int num_of_lines){
	if(result.size() <= 1 || result.size() >= 4)
		return false;
	if(result[0] != "Insert" && result[0] != "Update" && result[0] != "Delete")
		return false;
	if((result[0] == "Update" || result[0] == "Insert") && result.size() != 3)
		return false;
	int i = atoi(result[1].c_str());
	if(i <= 0 || (i > num_of_lines && result[0] == "Update") || (i > (num_of_lines + 1) && result[0] == "Insert"))
		return false;
	if(result[0] != "Delete")
		if(result[2][0] != '"' || result[2][result[2].length() - 1] != '"')
			return false;
	return true;
}

void Editor::add_new_version_to_chapter(int chapter_number){
	if(!has_permission(chapter_number))
		return;
	edit_chapter[chapter_number - 1]->add_version(new_version[chapter_number - 1]);
	//delete new_version[chapter_number - 1];
	new_version[chapter_number - 1] = new Version();
	started_new_version[chapter_number - 1] = false;
}

void Editor::delete_new_version(int chapter_number){
	if(!has_permission(chapter_number))
		return;
	new_version[chapter_number - 1]->undo();
	delete new_version[chapter_number - 1];
	new_version[chapter_number - 1] = new Version();
	started_new_version[chapter_number - 1] = false;
}

void Editor::push_to_server(int chapter_number){
	if(!has_permission(chapter_number))
		return;
	if(version_to_return[chapter_number - 1] != -1){
		if(user_position[chapter_number - 1] == "author"){
			cout << "Your are not owner of the book to complete these changes. Please reload your chapter\n";
			return;
		}
		else{
			send_return_to_previous_version_to_server(chapter_number);
		}
	}
	int num_of_new_versions = edit_chapter[chapter_number - 1]->num_of_versions() - num_of_versions_before_editing[chapter_number - 1];
	if(num_of_new_versions == 0){
		cout << "There isn't any new submited version to push to server\n";
		return;
	}
	string server_query = "Update_chapter," + book_name[chapter_number - 1] + ',' + edit_chapter[chapter_number - 1]->get_title();
	server_query += "," + user_position[chapter_number - 1] + ',' + int_to_string(num_of_new_versions);
	for (int i = 0; i < num_of_new_versions; ++i)
	{
		Version* shorter = edit_chapter[chapter_number - 1]->get_versions(i + num_of_versions_before_editing[chapter_number - 1]);
		server_query += ',' + int_to_string(shorter->num_of_commands()); // to know size of commands of each version
		server_query += ',' + shorter->to_string();	
	}
	string result = userUI->send(server_query);
	cout << result << endl;
	num_of_versions_before_editing[chapter_number - 1] += num_of_new_versions;
}

void Editor::send_return_to_previous_version_to_server(int chapter_number){
	string server_query = "Return_chapter," + book_name[chapter_number - 1] + ',' + edit_chapter[chapter_number - 1]->get_title();
	server_query += ',' + int_to_string(version_to_return[chapter_number - 1]);
	cout << userUI->send(server_query) << endl;
}

void Editor::return_to_previous_version(int chapter_number){
	if(!has_permission(chapter_number))
		return;
	if(edit_chapter[chapter_number - 1]->num_of_versions() == 0){
		cout << "This book doesn't have any version to return to!! First add some versions.\n";
	}
	cout << "To which version you want to return?\n";
	int return_version_number = get_version_number(chapter_number);
	edit_chapter[chapter_number - 1]->return_to_version(return_version_number);
	delete_new_version(chapter_number);
	version_to_return[chapter_number - 1] = return_version_number;
	num_of_versions_before_editing[chapter_number - 1] = edit_chapter[chapter_number-1]->num_of_versions();
}

void Editor::reload_chapter(int chapter_number){
	string server_query =  "Get_chapter_by_title," + book_name[chapter_number-1];
	server_query += "," + userUI->get_username() + "," + edit_chapter[chapter_number-1]->get_title();
	
	string server_response = userUI->send(server_query);
	vector<string> parsed_result = split_line(server_response, ',');
	parsed_result.erase(parsed_result.begin());
	server_response = make_line(parsed_result);

	delete edit_chapter[chapter_number-1];
	edit_chapter[chapter_number-1] = new Chapter(server_response);
	num_of_versions_before_editing[chapter_number-1] = edit_chapter[chapter_number-1]->num_of_versions();
	started_new_version[chapter_number-1] = false;
	version_to_return[chapter_number-1] = -1;
	delete new_version[chapter_number-1];
	new_version[chapter_number-1] = new Version();
}

bool Editor::has_permission(int chapter_number){
	if(user_position[chapter_number - 1] == "noPos"){
		cout << "You don't have permission to complete this job" << endl;
		return false;
	}
	return true;
}



void Editor::show_chapters_list(){
	for (int i = 0; i < edit_chapter.size(); ++i){
		cout << i+1 << ". chapter: '" << edit_chapter[i]->get_title() << "' from book: '"<< book_name[i] << "'" << endl;
	}
}

void Editor::show_introduction(bool started_new_version){
	cout << "Select what you want to do:" << endl;
	if(!started_new_version)
		cout << "\t1.Add a new version" << endl;
	else{
		cout << "\t1.Continue Editing" << endl;
		cout << "\t\t7.Submit new version" << endl;
		cout << "\t\t8.Delete new version" << endl;
	}
	cout << "\t2.Look at versions" << endl;	
	cout << "\t3.Return to a previous version" << endl;
	cout << "\t4.Push updates to server" << endl;
	cout << "\t5.Update chapter(get it again from the server)" << endl;
	cout << "\t6.Back to editor chapter menu" << endl;
}

void Editor::show_commands_structure(){
	cout << "These are our edit commands:" << endl;
	cout << "\tInsert, line_number, \" new_line_text \"" << endl;
	cout << "\tUpdate, line_number, \" updated_text \"" << endl;	
	cout << "\tDelete, line_number" << endl;
	cout << "\tQuit" << endl;		
}
