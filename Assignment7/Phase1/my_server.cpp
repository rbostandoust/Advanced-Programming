#include "my_server.h"

using namespace std;

MyServer::MyServer(){
	my_rep = new Repository();
	admin = new Admin("admin", "admin123");

	users.push_back(new User("mamaReza", "123"));
	users.push_back(new User("ali", "123"));
	users.push_back(new User("a", "a"));


	// vector<User*> a;
	// a.push_back(find_user("ali"));
	// a.push_back(find_user("admin"));
	// my_rep->add_book("asb" , find_user("mamaReza") , a);


	// vector<string> queries;
	// queries.push_back("salam");
	// queries.push_back("khooBn? her her");
	// queries.push_back(":D");
	// queries.push_back("manam ok am");
	// queries.push_back("b darak? :( ");
	// my_rep->find_book("asb")->add_chapter("fasl e 1", 1, queries);
}

string MyServer::recieve(string command){
	vector<string> result = split_line(command, ',');
	string server_response;
	if(result[0] == "Log_in"){
		result.erase(result.begin());
		server_response = log_in(result);
	}
	else if(result[0] == "Register"){
		result.erase(result.begin());
		server_response = add_user(result);
	}
	else if(result[0] == "Add_book"){
		result.erase(result.begin());
		try{
			server_response = add_book(result);
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "List_books"){
		result.erase(result.begin());
		server_response = my_rep->list_books(find_user(result[0]));
	}
	else if(result[0] == "Select_book"){
		result.erase(result.begin());
		try{
			server_response = my_rep->get_book_chapters_title(result[0], find_user(result[1]));
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Add_chapter"){
		result.erase(result.begin());
		try{
			server_response = add_chapter(result);
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Clone_chapter"){
		result.erase(result.begin());
		try{
			server_response = get_chapter(result);
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Update_chapter"){
		result.erase(result.begin());
		try{
			server_response = Update_chapter(result);
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Get_chapter_by_title"){
		result.erase(result.begin());
		try{
			server_response = get_chapter_by_title(result);
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Return_chapter"){
		result.erase(result.begin());
		try{
			my_rep->find_book(result[0])->find_chapter_by_name(result[1])->return_to_version(atoi(result[2].c_str()));
			server_response = "Chapter returned to version " + result[2]+ " successfully";
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Publish"){
		my_rep->find_book(result[1])->set_status(published);
	}
	else if(result[0] == "Export_HTML"){
		my_rep->find_book(result[1])->export_HTML();
	}
	else if(result[0] == "Add_author"){
		try{
			my_rep->find_book(result[1])->add_author(find_user(result[2]));
			server_response = "Author was added successfully";
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Remove_author"){
		try{
			my_rep->find_book(result[1])->remove_author(find_user(result[2]));
			server_response = "Author was removed successfully";
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Change_book_name"){
		try{
			if(my_rep->is_existing(result[2]))
				throw Exeption("Existing");
			my_rep->find_book(result[1])->set_name(result[2]);
			server_response = "Book name chaneged.";
		}
		catch(Exeption ex){
			server_response = ex.get_massage();
		}
	}
	else if(result[0] == "Acceptable_books"){
		server_response = my_rep->get_wating_for_approval_books();
	}
	else if(result[0] == "Admin_order"){
		result.erase(result.begin());
		if(result[1] == "1")
			my_rep->find_book(result[0])->set_status(writing);
		else
			my_rep->delete_book(result[0]);
	}
	
	return server_response;
}

string MyServer::add_user(vector<string>& queries){
	if(find_user(queries[0]))
		return "There is an existing user with this username!!";
	else{
		User* new_user = new User(queries[0], queries[1]);
		users.push_back(new_user);
	}
	return "Register was successful!\nNow you can log in with your account.";
}

User* MyServer::find_user(string username){
	if(username == admin->get_username())
		return admin;
	for (int i = 0; i < users.size(); ++i)
		if(username == users[i]->get_username())
			return users[i];
	return NULL;
}

string MyServer::log_in(vector<string>& queries){
	User* curr = find_user(queries[0]); 
	if(curr){
		if(curr->get_password() == queries[1])
			return queries[0];
		else
			return "";
	}
	else
		return "";	
}

string MyServer::add_book(std::vector<std::string>& queries){
	string book_name = queries[0];
	if(my_rep->is_existing(book_name))
		throw Exeption("Existing");
	queries.erase(queries.begin());
	User* owner = find_user(queries[0]);
	if(owner == NULL)
		return "Owner wasn't found";
	queries.erase(queries.begin());
	std::vector<User*> authors;
	for (int i = 0; i < queries.size(); ++i){
		authors.push_back(find_user(queries[i]));
		if(authors[i] == NULL)
			return "author " + queries[i] + " wasn't found";
	}
	my_rep->add_book(book_name, owner, authors);
	return "Book was added successfully";
}

string MyServer::add_chapter(std::vector<std::string>& queries){
	string book_name = queries[0];
	string chapter_name = queries[1];
	int chapter_number = atoi(queries[2].c_str());
	for (int i = 0; i < 3; ++i)
		queries.erase(queries.begin());
	my_rep->find_book(book_name)->add_chapter(chapter_name, chapter_number, queries);
	return "Chapter was added successfully";
}

string MyServer::get_chapter(vector<string>& queries){
	string result;
	string book_name = queries[0];
	string username = queries[1];
	int chapter_number = atoi(queries[2].c_str());
	for (int i = 0; i < 3; ++i)
		queries.erase(queries.begin());
	result = my_rep->find_book(book_name)->get_user_position(find_user(username));
	result += ',' + my_rep->find_book(book_name)->find_chapter_by_number(chapter_number)->to_string();
	return result;
}

string MyServer::get_chapter_by_title(vector<string>& queries){
	string result;
	string book_name = queries[0];
	string username = queries[1];
	string chapter_title = queries[2];
	for (int i = 0; i < 3; ++i)
		queries.erase(queries.begin());
	result = my_rep->find_book(book_name)->get_user_position(find_user(username));
	result += ',' + my_rep->find_book(book_name)->find_chapter_by_name(chapter_title)->to_string();
	return result;
}

string MyServer::Update_chapter(vector<string>& queries){
	string book_name = queries[0];
	string chapter_title = queries[1];
	string user_position = queries[2];
	int num_of_new_versions = atoi(queries[3].c_str());
	delete_first_n_block_of_vector(queries, 4);
	my_rep->find_book(book_name)->find_chapter_by_name(chapter_title)->add_unparsed_versions(queries);
	my_rep->find_book(book_name)->find_chapter_by_name(chapter_title)->apply_new_versions(num_of_new_versions);
	return "Chapter was updated successfully\n";
}
