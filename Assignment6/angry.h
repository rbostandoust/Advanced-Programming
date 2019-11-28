#ifndef __ANGRY_H__
#define __ANGRY_H__

#include "child.h"
#include <cmath>

class Angry : public Child
{
public:
	Angry(int _id, int _r, bool _f, Velocity _v, Point _p, Behaviour _b) 
		: Child(_id, _r, _f, _v, _p, _b){ type = "Angry"; fix_behaviour();};
	void fix_behaviour();
	void deal_with(Child* another_child);
};

#endif