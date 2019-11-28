#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string>
#include "chapter.h"
#include "utility.h"

class Chapter;

class Command
{
public:
	Command(int _l_n, std::string _d_v, std::string _u_v, std::string _t, Chapter* _c) 
		: line_number(_l_n), do_value(_d_v), undo_value(_u_v), type(_t), my_chapter(_c) {};
	virtual void apply_change() = 0;
	virtual void undo_change() = 0;
	std::string to_string();
protected:
	Chapter* my_chapter;
	int line_number;
	std::string do_value;
	std::string undo_value;
	std::string type;
};

class Update : public Command
{
public:
	Update(int _l_n, std::string _d_v, std::string _u_v, std::string _t, Chapter* _c) 
		: Command(_l_n, _d_v, _u_v, _t, _c) {};
	void apply_change();
	void undo_change();	
};

class Delete : public Command
{
public:
	Delete(int _l_n, std::string _d_v, std::string _u_v, std::string _t, Chapter* _c) 
		: Command(_l_n, _d_v, _u_v, _t, _c) {};
	void apply_change();	
	void undo_change();
};

class Insert : public Command
{
public:
	Insert(int _l_n, std::string _d_v, std::string _u_v, std::string _t, Chapter* _c) 
		: Command(_l_n, _d_v, _u_v, _t, _c) {};
	void apply_change();	
	void undo_change();
};

#endif