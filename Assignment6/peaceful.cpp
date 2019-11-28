#include "peaceful.h"

void Peaceful::fix_behaviour(){
	if(behaviour.anger > 30)
		behaviour.anger = 30;
	if(behaviour.charisma < 50)
		behaviour.charisma = 50;
	if(behaviour.courage < 30)
		behaviour.courage = 30;
	Child::fix_behaviour();
}

void Peaceful::deal_with(Child* another_child){
	if(fragile)
		check_fragility(another_child);
	if(another_child->get_anger() > 70 && another_child->get_courage() > 50){
		// Courage of a coward guy is always 0 => it does't need another condition.... 
		changes.delta_radius -= 
			floor((1 - (double)(another_child->get_charisma() + another_child->get_courage()) / 200) * 0.8 * another_child->get_radius());
		changes.delta_behaviour.courage -= 10;
	}
	else if(another_child->get_courage() > 30 && another_child->get_charisma() > 50){
		// setting delta_v to an amount that causes equal speed after adding to v
		changes.delta_v.x += (another_child->get_velocity().x - v.x) / 2;
		changes.delta_v.y += (another_child->get_velocity().y - v.y) / 2;

		changes.delta_behaviour.charisma += 2;
		changes.delta_behaviour.courage += 2;
		num_of_unions ++;
	}
	else
		Child::deal_with(another_child);
	changes.num_of_collisions ++;
}

void Peaceful::effect_changes(){
	Child::effect_changes();
	// coureges (if equal or more than 2 peaceful guys children him) =+ ( num of peaceful children in union ) * 5
	if(num_of_unions > 2)
		behaviour.courage += 5 * num_of_unions;
	num_of_unions = 0;
}
