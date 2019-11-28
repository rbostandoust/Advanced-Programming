#include "angry.h"

void Angry::fix_behaviour(){
	if(behaviour.anger < 70)
		behaviour.anger = 70;
	behaviour.charisma = 20;
	if(behaviour.courage < 50)
		behaviour.courage = 50;
	Child::fix_behaviour();
}

void Angry::deal_with(Child* another_child){
	if(fragile)
		check_fragility(another_child);
	if(another_child->get_anger() > 70){
		if(radius < another_child->get_radius()){
			changes.delta_radius -= floor(0.2 * radius);
			changes.delta_behaviour.anger += 5;
		}
	}
	else if(another_child->get_courage() > 30 && another_child->get_charisma() > 50){
		changes.delta_radius += 
			floor((1 - (double)(another_child->get_charisma() + another_child->get_courage()) / 200) * 0.8 * another_child->get_radius());
	}
	else
		Child::deal_with(another_child);
	changes.num_of_collisions ++;
}