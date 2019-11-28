#include "child.h"

Child::Child(int _id, int _r, bool _f, Velocity _v, Point _p, Behaviour _b) 
	: id(_id), radius(_r), v(_v), pos(_p), behaviour(_b)
{
	clear_changes(true);
};

void Child::fix_behaviour(){
	if(behaviour.anger > 100)
		behaviour.anger = 100;
	if(behaviour.charisma >100)
		behaviour.charisma = 100;
	if(behaviour.courage > 100)
		behaviour.courage = 100;
}


void Child::print_status(){
	std::cout << id << ", ";
	if(!death){
		std::cout << type << ", " << floor(pos.x * 10 ) / 10.0 << ", " << floor(pos.y * 10) / 10.0 <<", ";
		//std::cout << floor(v.x * 10) / 10.0 << ", " << floor(v.y * 10) / 10.0 << ", " ;
		std::cout << radius << ", ";
		std::cout << behaviour.anger << ", " << behaviour.charisma << ", " << behaviour.courage;
	}
	else
		std::cout << "KIA";
	std::cout << std::endl;
}

void Child::move(int dt){
	pos.x += v.x * dt;
	pos.y += v.y * dt;
}

bool Child::is_nocked_with(Child* another_child){
	double distance = sqrt(pow(pos.x - another_child->pos.x, 2) + pow(pos.y - another_child->pos.y, 2));
	if(distance <= radius + another_child->radius)
		return true;
	return false;
}

void Child::deal_with(Child* another_child){
	double first_factor = (double)(radius*radius - another_child->radius*another_child->radius) / (radius*radius + another_child->radius*another_child->radius);
	double second_factor = (double)(2 * another_child->radius*another_child->radius) / (radius*radius + another_child->radius*another_child->radius);
	
	double new_delta_v_x = (first_factor * v.x) + (second_factor * another_child->v.x) - v.x; 
	double new_delta_v_y = (first_factor * v.y) + (second_factor * another_child->v.y) - v.y;
	changes.delta_v.x = ((changes.delta_v.x * changes.num_of_collisions) + new_delta_v_x) / (changes.num_of_collisions + 1);
	changes.delta_v.y = ((changes.delta_v.y * changes.num_of_collisions) + new_delta_v_y) / (changes.num_of_collisions + 1);
}

void Child::check_fragility(Child* another_child){
	if( (radius + another_child->radius) > 20){
		if(radius < 6)
			death = true;
		else
			changes.is_broken = true;
	}
}

void Child::clear_changes(bool is_it_first_time){
	changes.delta_radius = 0;
	changes.delta_v.x = 0;
	changes.delta_v.y = 0;
	changes.delta_behaviour.anger = 0;
	changes.delta_behaviour.charisma = 0;
	changes.delta_behaviour.courage = 0;
	changes.num_of_collisions = 0;
	if(is_it_first_time){
		death = false;
		changes.is_broken = false;
	}
}

void Child::effect_changes(){
	radius += changes.delta_radius;
	v.x += changes.delta_v.x;
	v.y += changes.delta_v.y;
	behaviour.anger += changes.delta_behaviour.anger;
	behaviour.charisma += changes.delta_behaviour.charisma;
	behaviour.courage += changes.delta_behaviour.courage;
	if(radius <= 0 || behaviour.anger >= 100)
		death = true;
}

void Child::refelect_v(int x_dir, int y_dir){
	v.x = x_dir * v.x;
	v.y = y_dir * v.y;
}
