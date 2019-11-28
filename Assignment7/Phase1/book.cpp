#include "book.h"

using namespace std;

Book::Book(string _n, User* _o, vector<User*> _a)
	: name(_n), owner(_o), authors(_a) {};

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
			result += ","; 	
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

void Book::export_HTML(){
	ofstream out(("HTML_Books/" + name + ".html").c_str());
	string menu;
	for (int i = 0; i < chapters.size(); ++i)
		menu += "<a href=\"#" + int_to_string(i)+  "\">" + int_to_string(i) + ". " + chapters[i]->get_title() + "</a><br>";
	string chapters_content;
	for (int i = 0; i < chapters.size(); ++i)
	{
		chapters_content += "<p>";
		chapters_content += "<span  id=\"" + int_to_string(i) + "\">" + chapters[i]->get_title() + "</span></br>";
		for (int j = 0; j < chapters[i]->num_of_lines(); ++j)
			chapters_content += chapters[i]->get_line(j + 1) + "</br>";
		chapters_content += "</p>";
	}
	out << "<!DOCTYPE html>" <<
	"<html>" <<
		"<head>" <<
			"<title>" << name << "</title>" <<
			"<style>" <<
				"p{margin-left: 100px; margin-right: 100px; margin-ip:50px; border: 3px solid gray;}" <<
				"p.middle{text-align: center; background-color: rgb(153, 153, 102);}" <<
				"span{text-align: center; font-weight: bold;}" <<
			"</style>" <<
		"</head>" <<
		"<body style=\"background-color: rgb(173, 173, 133);\">" <<
			"<p class=\"middle\">" << 
			 	name << "<br>" << 
			 	menu <<
			"</p>" << chapters_content <<
		"</body>" <<
	"</html>";
	out.close();
}