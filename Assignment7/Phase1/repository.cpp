#include "repository.h"

using namespace std;

Repository::Repository(){}

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
		string pos = books[i]->get_user_position(user);
		if(pos != "")
			result += " => " + pos;
		if(i != books.size() - 1)
			result += ","; 	
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
	result = book_status + "," + selected_book->get_user_position(user) + "," + selected_book->get_chapters_title();
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

string Repository::get_wating_for_approval_books(){
	string wating_for_approval_books = ",";
	for (int i = 0; i < books.size(); ++i)
		if(books[i]->get_status() == waiting_for_approval)
			wating_for_approval_books += books[i]->get_name() + "," + books[i]->get_owner_username() + ",";
	wating_for_approval_books.erase(wating_for_approval_books.begin() + wating_for_approval_books.length() - 1); // for removing extra ,
	return wating_for_approval_books;
}

bool Repository::is_first_book(User* user){
	for (int i = 0; i < books.size(); ++i)
		if(books[i]->get_owner_username() == user->get_username())
			return false;
	return true;
}
