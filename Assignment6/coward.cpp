#include "coward.h"

void Coward::fix_behaviour(){
	if(behaviour.anger < 0)
		behaviour.anger = 0;
	behaviour.charisma = 0;
	behaviour.courage = 0;
	Child::fix_behaviour();
}

void Coward::deal_with(Child* another_child){
	if(fragile)
		check_fragility(another_child);
	changes.delta_behaviour.anger += 5;
	if(another_child->get_anger() > 70)
		death = true;
	else
		Child::deal_with(another_child);
	changes.num_of_collisions ++;
}