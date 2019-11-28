#include "repository.h"

using namespace std;

Repository::Repository(){
	
}

Repository::~Repository(){
	ofstream out("../server_data/books");
	out << books.size() << endl;
	out.close();
	for (int i = 0; i < books.size(); ++i)
		delete books[i];
	books.clear();
	cout << "Repository destructor called\n";
}

void Repository::add_book(string name, User* owner, vector<User*> authors){
	Book* new_book = new Book(name, owner, authors);
	if(is_first_book(owner) && owner->get_username() != "admin")
		new_book->set_status(waiting_for_approval);
	else
		new_book->set_status(writing);
	books.push_back(new_book);
}

void Repository::delete_book(string book_name){
	for (int i = 0; i < books.size(); ++i)
		if(books[i]->get_name() == book_name){
			delete books[i];
			books.erase(books.begin() + i);
			return;
		}
}

string Repository::list_books(User* user){
	string result = "";
	for (int i = 0; i < books.size(); ++i)
	{
		result += books[i]->get_name();
		result += DELIMETER + books[i]->get_user_position(user);
		result += DELIMETER + status_to_string(books[i]->get_status());
		int num_of_chapters = books[i]->num_of_chapters();
		result += DELIMETER + int_to_string(num_of_chapters);
		if(num_of_chapters != 0)
			result += DELIMETER;
		result += books[i]->get_chapters_title();
		if(i != books.size() - 1)
			result += DELIMETER;
	}
	return result;
}

string Repository::get_book_chapters_title(string book_name, User* user){
	string result;
	Book* selected_book = find_book(book_name);
	if(selected_book->get_status() == waiting_for_approval)
		throw(Exeption("NotApproved"));
	string book_status = "writing";
	if(selected_book->get_status() == published)
		book_status = "published";
	result = book_status + DELIMETER + selected_book->get_user_position(user) + DELIMETER + selected_book->get_chapters_title();
	return result;
}

Book* Repository::find_book(string book_name){
	for (int i = 0; i < books.size(); ++i)
		if(books[i]->get_name() == book_name)
			return books[i]; 
	throw Exeption("UnFoundBook");
}

bool Repository::is_existing(string book_name){
	for (int i = 0; i < books.size(); ++i)
		if(books[i]->get_name() == book_name)
			return true;
	return false;
}

string Repository::get_waiting_for_approval_books(){
	string waiting_for_approval_books = "";
	// waiting_for_approval_books += DELIMETER;
	for (int i = 0; i < books.size(); ++i)
		if(books[i]->get_status() == waiting_for_approval)
			waiting_for_approval_books += books[i]->get_name() + DELIMETER + books[i]->get_owner_username() + DELIMETER;
	if(waiting_for_approval_books.length() > 0)
		waiting_for_approval_books.erase(waiting_for_approval_books.end() - 1); // for removing extra DELIMETER
	return waiting_for_approval_books;
}

bool Repository::is_first_book(User* user){
	for (int i = 0; i < books.size(); ++i)
		if(books[i]->get_owner_username() == user->get_username())
			return false;
	return true;
}
