#include "user_interface.h"

using namespace std;

UserInterface::UserInterface(std::string address, int port){
	username = "";
	socket = new ClientSocket(address, port);
}

void UserInterface::handle(){
	string command = "a";
	while(!logged_in()){
		if(command != "" && command != "\n")
			show_log_in_introduction();
		getline(cin, command);
		if(command == "Register")
			register_new_user();
		else if(is_log_in_command_ok(command)){
			remove_space(command);
			username = send_then_receive(command);
			if(username == "")
				cout << "There isn't any user with this username or password..." << endl;
			else{
				cout << "User " << username << " logged in successful.\n";
				editor = new Editor(this);
			}
		}
	}
	while(logged_in()){
		show_introductoin(username);
		string command;
		cin >> command;
		flush_input();
		if(command == "Log_out")
			log_out_user();
		else if(command == "Add_book")
			add_book();
		else if(command == "List_books")
			get_books_list();
		else if(command == "Select_book")
			select_book();
		else if(command == "My_editor")
			editor->run();
		else if(command == "Accept_books" && username == ADMIN_USERNAME)
			accept_books_system_run();
		else
			cout << "Wrong command has been entered!! Please try again" << endl;
	}
}


bool UserInterface::logged_in(){
	return (username != "");
}


bool UserInterface::is_log_in_command_ok(string log_in_command){
	remove_space(log_in_command);
	vector<string> result = split_line(log_in_command, DELIMETER);
	if(result.size() == 3 && result[0] == "Log_in")
		return true;
	return false;
}

void UserInterface::register_new_user(){
	string un, ps, rps;
	cout << "Please choose a username:" << endl;
	cin >> un;
	cout << "Please choose a password:" << endl;
	cin >> ps;
	cout << "Please repeat your password:" << endl;
	cin >> rps;
	flush_input();
	if(ps != rps){
		cout << "The passwords doesn't match... Please try again" << endl;
		register_new_user();
		return;
	}
	string server_query = "Register";
	server_query += DELIMETER + un + DELIMETER + ps;
	cout << send_then_receive(server_query) << endl;
}

void UserInterface::log_out_user(){
	delete editor;
	cout << username << " logged out successfully!" << endl;
	username = "";
}

void UserInterface::add_book(){
	string book_name, server_query = "Add_book";
	server_query += DELIMETER;
	cout << "Please enter book name:" <<endl;
	getline_manual(book_name);
	server_query += book_name + DELIMETER + username;
	cout << "Please enter authors usernames(Enter " << END_SYMBOL << " when you finished):" <<endl;
	string usernames = get_till_end_symbol(END_SYMBOL, DELIMETER);
	string result = send_then_receive(server_query + usernames);
	if(result == "Existing")
		result = "There is an existing book with this name in the repository.";
	cout << result << endl;
}

void UserInterface::get_books_list(){
	string server_query = "List_books";
	server_query += DELIMETER + username;
	string server_response = send_then_receive(server_query);
	print_parsed_line(server_response);
}

void UserInterface::select_book(){
	string book_name;
	cout << "Enter book name:\n";
	getline_manual(book_name);
	string server_query = "Select_book";
	server_query += DELIMETER + book_name + DELIMETER + username;
	string server_response = send_then_receive(server_query);
	if(server_response == "UnFoundBook"){
		cout << "Book Didn't found!!\n";
		return;
	}
	else if(server_response == "NotApproved"){
		cout << "Book hasn't been approved yet!!\n";
		return;
	}
	vector<string> result = split_line(server_response, DELIMETER);
	string book_status = result[0];
	string player_post = result[1];

	if(book_status != "published" && player_post == "noPost"){
		cout << "You don't have permission to Access this book!!" << endl;
		return;
	}

	delete_first_n_block_of_vector(result, 2);
	
	if(result.size() == 1 && (result[0] == "" || result[0] == player_post))
		result.erase(result.begin());
	bool no_chapter = (result.size() == 0);
	if(no_chapter)
		cout << "This book has no chapter.\n";
	else{
		cout << "Here are chapters of the book:\n";
		for (int i = 0; i < result.size(); ++i)
			cout << "\t" << i+1 << ":" << result[i] << endl;
	}
	while(true){
		no_chapter = (result.size() == 0);
		show_book_introduction(no_chapter, book_status, player_post);
		string command;
		cin >> command;
		flush_input();
		if(command == "Back_to_menu")
			break;
		else if(command == "Add_chapter" && player_post != "noPost" && book_status != "published")
			add_chapter(book_name, result);
		else if(command == "Clone_chapter" && ((player_post == "noPost" && book_status == "published") || player_post != "noPost")){
			if(no_chapter){
				cout << "This book doesn't hve any chapter to edit... Please first add a chapter\n";
				continue;
			}
			clone_chapter(book_name, result.size());
			break;
		}
		else if(command == "Publish" && player_post == "owner" && book_status != "published"){
			string server_query = "Publish";
			server_query += DELIMETER + book_name;
			send_then_receive(server_query);
			cout << "The book has been published\n";
			break;
		}
		else if(command == "Add_author" && player_post == "owner" && book_status != "published"){
			add_author(book_name);
		}
		else if(command == "Remove_author" && player_post == "owner" && book_status != "published"){
			remove_author(book_name);
		}
		else if(command == "Change_book_name" && player_post == "owner" && book_status != "published"){
			change_book_name(book_name);
			break;
		}
		else if(command == "Export_HTML" && book_status == "published"){
			export_HTML(book_name);
			break;
		}
		else
			cout << "Wrong command has been entered!! Please try again" << endl;
	}
}

void UserInterface::add_chapter(std::string book_name, vector<string>& chapters_name){
	int chapter_number = get_chapter_number(chapters_name.size(), true);
	string chapter_title, server_query;
	cout << "Please enter chapter title:" <<endl;
	getline_manual(chapter_title);
	server_query = "Add_chapter";
	server_query += DELIMETER + book_name + DELIMETER + chapter_title + DELIMETER + int_to_string(chapter_number);
	vector<string> new_chapter_lines;
	bool finished = false;
	while(!finished){
		show_add_content_to_new_chapter_introduction();
		string command;
		cin >> command;
		flush_input();
		if(command == "No_content")
			finished = true;
		else if(command == "By_file"){
			try{
				get_content_from_file(new_chapter_lines);
				for (int i = 0; i < new_chapter_lines.size(); ++i)
					cout <<"\t\t"<< new_chapter_lines[i] << endl;
				if(new_chapter_lines.size() > 0)
					server_query += DELIMETER + make_line(new_chapter_lines);
				finished = true;
			}
			catch(Exeption ex){
				if(ex.get_massage() == "NoFileExist")
					cout << "No file exist with this name!\n";
			}
		}
		else if(command == "By_terminal"){
			server_query += get_content_from_terminal();
			finished = true;
		}
		else
		 	cout << "Wrong command has been entered!! Please try again" << endl;
	}
	string result = send_then_receive(server_query);
	if(result == "Chapter was added successfully")
		chapters_name.push_back(chapter_title);
	cout << result << endl;
}
	
void UserInterface::get_content_from_file(vector<string>& new_chapter_lines){
	string name;
	cout << "Enter file name:" << endl;
	getline_manual(name);
	vector<string> s_lines = read_file_content(name);
	for (int i = 0; i < s_lines.size(); ++i)
		new_chapter_lines.push_back(s_lines[i]);
	cout << "Datas were read successfully!!\n";
}

string UserInterface::get_content_from_terminal(){
	cout << "Enter your content line by line (Enter "<< END_SYMBOL <<" to end)" << endl;
	string result = get_till_end_symbol(END_SYMBOL, DELIMETER);
	return result;
}

void UserInterface::clone_chapter(std::string book_name, int num_of_chapters){
	int chapter_number = get_chapter_number(num_of_chapters);
	string server_query =  "Clone_chapter";
	server_query += DELIMETER + book_name + DELIMETER + username + DELIMETER + int_to_string(chapter_number);
	string server_response = send_then_receive(server_query);
	if(server_response == "UnFoundBook"){
		cout << "Book didn't find!!" <<endl;
		return;
	}
	vector<string> parsed_result = split_line(server_response, DELIMETER);
	string player_pos = parsed_result[0];
	parsed_result.erase(parsed_result.begin());
	server_response = make_line(parsed_result);
	editor->add_chapter(book_name, player_pos, server_response);
	cout << "Chapter has been successfully added to your editor... Now you can edit it\n";
}

int UserInterface::get_chapter_number(int num_of_chapters, bool for_new_chapter){
	int chapter_number = -1;
	while(chapter_number < 0 || chapter_number > num_of_chapters + (for_new_chapter ? 1 : 0)){
		cout << "Please enter the number of new chapter(between " << 1 << " and " << num_of_chapters + (for_new_chapter ? 1 : 0) << "):" <<endl;
		cin >> chapter_number;
		if(chapter_number < 0 || chapter_number > num_of_chapters + (for_new_chapter ? 1 : 0))
			cout << "Number should be between " << 1 << " and " << num_of_chapters + (for_new_chapter ? 1 : 0) << "... Please try again!!" <<endl;
	}
	return chapter_number;
}

string UserInterface::send_then_receive(string massage){
	socket->send(massage);
	return socket->receive();
}

void UserInterface::add_author(string book_name){
	string new_author;
	cout << "Enter new auther username:" << endl;
	cin >> new_author;
	flush_input();
	string server_query = "Add_author";
	server_query += DELIMETER + book_name + DELIMETER + new_author;
	string result = send_then_receive(server_query);
	if(result == "ExistingAuthor")
		result = "There is an existing author with this username in the book author's list.";
	cout << result << endl;
}

void UserInterface::remove_author(string book_name){
	string author;
	cout << "Enter auther username:" << endl;
	cin >> author;
	flush_input();
	string server_query = "Remove_author";
	server_query += DELIMETER + book_name + DELIMETER + author;
	string result = send_then_receive(server_query);
	if(result == "NoAuthor")
		result = "There isn't aby author in the book author's list with this username.";
	cout << result << endl;
}

void UserInterface::change_book_name(string pre_book_name){
	string new_book_name;
	cout << "Enter new name of book :\n";
	cin >> new_book_name;
	flush_input();
	string server_query = "Change_book_name";
	server_query += DELIMETER + pre_book_name + DELIMETER + new_book_name;
	string result = send_then_receive(server_query);
	if(result == "Existing")
		result = "There is an existing book with this name.";
	cout << result << endl;
}

void UserInterface::accept_books_system_run(){
	string accepable_books = send_then_receive("Acceptable_books");
	if(accepable_books == ""){
		cout << "There isn't any wating for approval book" <<endl;
		return;
	}
	vector<string> result = split_line(accepable_books, DELIMETER);
	int num_of_books = result.size() / 2;
	for (int i = 0; i < result.size(); i += 2)
		cout << (i/2) + 1<< ". Book: '" << result[i] << "' from user " << result[i+1] <<endl;
	while(true){
		cout << "Enter each book number to deal with it(enter 0 to Quit)" << endl;
		int command;
		cin >> command;
		flush_input();
		if(command == 0)
			break;
		if(command > 0 && command <= num_of_books){
			cout << "Do you accept this book?(1 = yes , 0 = no)" << endl;
			int order;
			cin >> order;
			flush_input();
			if(order ==0 || order == 1){
				string server_query = "Admin_order";
				server_query += DELIMETER + result[(command-1) * 2] + DELIMETER + int_to_string(order);
				send_then_receive(server_query);
			}
			else
				cout << "Wrong input\n";
		}
	}
}

void UserInterface::export_HTML(string book_name){
	string server_query = "Export_HTML";
	server_query += DELIMETER + book_name;
	string server_response = send_then_receive(server_query);
	vector<string> result = split_line(server_response, DELIMETER);
	
	string authors_list = "Book owner: " + result[0] + "<br>";
	int num_of_authors = atoi(result[1].c_str());
	delete_first_n_block_of_vector(result, 2);
	
	for (int i = 0; i < num_of_authors; ++i)
		authors_list += "Author " + int_to_string(i+1) + ":" + result[i] + "<br>";

	int num_of_chapters = atoi(result[num_of_authors].c_str());
	delete_first_n_block_of_vector(result, num_of_authors + 1);
	string menu;
	for (int i = 0; i < num_of_chapters; ++i)
		menu += "<a href=\"#" + int_to_string(i)+  "\">" + int_to_string(i + 1) + ". " + result[i] + "</a><br>";

	string chapters_content;
	for(int i = num_of_chapters; i < 2 * num_of_chapters; ++i)
	{
		chapters_content += "<p>";
		chapters_content += "<span  id=\"" + int_to_string(i - num_of_chapters) + "\">" + result[i - num_of_chapters] + "</span></br></br>";
		int chapter_lines = atoi(result[num_of_chapters].c_str());
		for (int j = 1; j <= chapter_lines; ++j)
			chapters_content += result[num_of_chapters + j] + "<br>";
		for (int k = 0; k <= chapter_lines; ++k)
			result.erase(result.begin() + num_of_chapters);
		chapters_content += "</p>";
	}

	ofstream out(("../HTML_Books/" + book_name + ".html").c_str());
	out << "<!DOCTYPE html>" <<
	"<html>" <<
		"<head>" <<
			"<title>" << book_name << "</title>" <<
			"<style>" <<
				"p{text-indent: 10px;margin-left: 100px; margin-right: 100px; margin-ip:50px; border: 3px solid gray;padding: 10px;}" <<
				"p.middle{text-align: center; background-color: rgb(153, 153, 102);}" <<
				"span{text-align: center; font-weight: bold;}" <<
			"</style>" <<
		"</head>" <<
		"<body style=\"background-color: rgb(173, 173, 133);\">" <<
			"<p class=\"middle\">" << 
			 	"<b>book name: " << book_name << "</b><br><br>" << 
			 	authors_list << "<br>" <<
			 	menu <<
			"</p>" << chapters_content <<
		"</body>" <<
	"</html>";
	out.close();
			
	cout << "The HTML version has been exported!\n";
}



/* show menu methods */
void UserInterface::show_introductoin(string _u){
	cout << "Please choose your request:" << endl;
	cout << "\tAdd_book" << endl;
	cout << "\tList_books" << endl;
	cout << "\tSelect_book" << endl;
	cout << "\tMy_editor" << endl;
	cout << "\tEdit_profile" << endl;
	if(_u == ADMIN_USERNAME)
		cout << "\tAccept_books" << endl;
	cout << "\tLog_out" << endl;
}

void UserInterface::show_log_in_introduction(){
	cout << "Please choose your request:" << endl;
	cout << "\tLog_in| username| password" << endl;
	cout << "\tRegister" << endl;	
}

void UserInterface::show_book_introduction(bool no_chapter, string book_status, string player_post){
	cout << "Please choose your request:" << endl;
	if(player_post != "noPost" && book_status != "published")
		cout << "\tAdd_chapter" << endl;
	if(!no_chapter){
		if((player_post == "noPost" && book_status == "published") || player_post != "noPost")
			cout << "\tClone_chapter" << endl;
	}
	if(player_post == "owner" && book_status != "published"){
		cout << "\tPublish" << endl;
		cout << "\tAdd_author" << endl;	
		cout << "\tRemove_author" << endl;	
		cout << "\tChange_book_name" << endl;
	}	
	if(book_status == "published"){
		cout << "\tExport_HTML" << endl;
	}
	cout << "\tBack_to_menu" << endl;
}

void UserInterface::show_add_content_to_new_chapter_introduction(){
	cout << "How do you want to add content to new chapter?" << endl;
	cout << "\tBy_file" << endl;
	cout << "\tBy_terminal" << endl;	
	cout << "\tNo_content" << endl;
}
