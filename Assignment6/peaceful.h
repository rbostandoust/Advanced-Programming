#ifndef __PEACEFUL_H__
#define __PEACEFUL_H__

#include "child.h"
#include <string>

class Peaceful : public Child
{
public:
	Peaceful(int _id, int _r, bool _f, Velocity _v, Point _p, Behaviour _b) 
		: Child(_id, _r, _f, _v, _p, _b){type = "Peaceful"; num_of_unions = 0; fix_behaviour();};
	void fix_behaviour();
	void deal_with(Child* another_child);
	void effect_changes();
private:
	int num_of_unions;
};

#endif