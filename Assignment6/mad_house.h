#ifndef __MAD_HOUSE_H__
#define __MAD_HOUSE_H__

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "yard.h"
#include "child.h"
#include "peaceful.h"
#include "angry.h"
#include "coward.h"

#define DELIMETER ','
#define STEP 5
#define PI 3.14159265

class BadInputExeption{};

class MadHouse
{
public:
	MadHouse();
	void add_child(Child* new_child);
	void get_inputs();
	void simulate(int T, int dt);
	void print_round_status(int round_num);
	void move_children(int dt);
	void highlight_and_determin_collision_with_wall();
	void highlight_collision_with_children();
	void determin_result_with_children();
	void delete_dead_children();
	void clear_memory();
	void break_broken_children();
	int get_last_child_id();
private:
	std::vector<Child*> children;
	Yard* yard;
};

void delete_space(std::string& line);
std::vector<std::string> split_by_camma(std::string& line);
Child* make_right_sub_class(int _id, int _r, bool _f, Velocity _v, Point _p, Behaviour _b, std::string type);

#endif