#include "book.h"

using namespace std;

Book::Book(string _n, User* _o, vector<User*> _a)
	: name(_n), owner(_o), authors(_a) {};


Book::~Book(){
	ofstream out("../server_data/books", ios::app);
	out << name << " " << chapters.size() << endl;
	out << owner->get_username() << " " << authors.size() << " ";
	for (int i = 0; i < authors.size(); ++i)
		out << authors[i]->get_username() << " ";
	out << endl;
	for (int i = 0; i < chapters.size(); ++i){
		out << chapters[i]->to_string() << endl;
		delete chapters[i];
	}
	out.close();
	chapters.clear();
	cout << "Book destructor called\n";
}


string Book::get_user_position(User* user){
	if(user == owner)
		return "owner";
	for (int i = 0; i < authors.size(); ++i)
		if(user == authors[i])
			return "author";
	return "noPos";
}

string Book::get_name(){
	return name;
}
void  Book::set_name(string _n){
	name = _n;
};


string Book::get_chapters_title(){
	string result = "";
	for (int i = 0; i < chapters.size(); ++i)
	{
		result += chapters[i]->get_title();
		if(i != chapters.size() - 1)
			result += DELIMETER; 	
	}
	return result;
}

string Book::get_owner_username(){
	return owner->get_username();
}


void Book::add_chapter(string Chapter_title, int chapter_number, vector<string> lines){
	Chapter* new_chapter = new Chapter(Chapter_title, lines);
	chapters.insert(chapters.begin() + chapter_number - 1, new_chapter);
}

void Book::add_chapter(Chapter* new_chapter){
	chapters.push_back(new_chapter);
}


Chapter* Book::find_chapter_by_name(string chapter_title){
	for (int i = 0; i < chapters.size(); ++i)
		if(chapters[i]->get_title() == chapter_title)
			return chapters[i];
	return NULL;
}

Chapter* Book::find_chapter_by_number(int chapter_number){
	if(chapter_number - 1 < chapters.size() && chapter_number - 1 >= 0)
		return chapters[chapter_number - 1];
	return NULL;
}

int Book::get_author_index(User* author){
	for (int i = 0; i < authors.size(); ++i)
		if(author == authors[i])
			return i;
	throw Exeption("NoAuthor");
}

void Book::remove_author(User* author){
	authors.erase(authors.begin() + get_author_index(author));
}

void Book::add_author(User* author){
	for (int i = 0; i < authors.size(); ++i)
		if(author == authors[i])
			throw Exeption("ExistingAuthor");
	authors.push_back(author);
}

string Book::export_HTML(){
	string authors_list, menu, content;
	authors_list = owner->get_username() + DELIMETER + int_to_string(authors.size()) + DELIMETER;
	for (int i = 0; i < authors.size(); ++i)
		authors_list += authors[i]->get_username() + DELIMETER;

	menu = int_to_string(chapters.size()) + DELIMETER;
	for (int i = 0; i < chapters.size(); ++i)
		menu += chapters[i]->get_title() + DELIMETER;

	for (int i = 0; i < chapters.size(); ++i){
		content += int_to_string(chapters[i]->num_of_lines()) + DELIMETER;
		for (int j = 0; j < chapters[i]->num_of_lines(); ++j)
			content += chapters[i]->get_line(j + 1) + DELIMETER;
	}

	return (authors_list + menu + content);
}