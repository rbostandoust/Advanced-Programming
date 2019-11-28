#ifndef __CHILD_H__
#define __CHILD_H__

#include <iostream>
#include <string>
#include <cmath>

struct Velocity
{
	Velocity(double _x,double _y) : x(_x) , y(_y){};
	Velocity(){};
	double x;
	double y;
};

struct Point
{
	Point(double _x,double _y) : x(_x) , y(_y){};
	Point(){};
	double x;
	double y;
};

struct Behaviour
{
	Behaviour(int _a, int _k ,int _c) : anger(_a), charisma(_k), courage(_c){};
	Behaviour(){};
	int anger;
	int charisma;
	int courage;	
};

struct Delta
{
	int delta_radius;
	Velocity delta_v;
	Behaviour delta_behaviour;
	int num_of_collisions;
	bool is_broken;
};

class Child
{
public:
	Child(int _id, int _r, bool _f, Velocity _v, Point _p, Behaviour _b);
	virtual void fix_behaviour();
	void print_status();
	void move(int dt);
	bool is_nocked_with(Child* another_child);
	virtual void deal_with(Child* another_child);
	void clear_changes(bool is_it_first_time = false);
	virtual void effect_changes();
	void refelect_v(int x_dir, int y_dir);
	void check_fragility(Child* another_child);

	int get_anger(){return behaviour.anger;}
	int get_charisma(){return behaviour.charisma;}
	int get_courage(){return behaviour.courage;}
	Behaviour get_behaviour(){return behaviour;}
	int get_radius(){return radius;}
	Velocity get_velocity(){return v;}
	Point get_pos(){return pos;}
	int get_id(){return id;}
	std::string get_type(){return type;}

	bool is_dead(){return death;}
	bool is_broken(){return changes.is_broken;}
	void set_death(){death = true;}
protected:
	int id;
	int radius;
	bool fragile;
	bool death;
	std::string type;
	Velocity v;
	Point pos;
	Behaviour behaviour;
	Delta changes;
};

#endif