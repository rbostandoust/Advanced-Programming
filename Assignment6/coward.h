#ifndef __COAWRD_H__
#define __COAWRD_H__

#include "child.h"
#include <cmath>

class Coward : public Child
{
public:
	Coward(int _id, int _r, bool _f, Velocity _v, Point _p, Behaviour _b) 
		: Child(_id, _r, _f, _v, _p, _b){type = "Coward"; fix_behaviour();};
	void fix_behaviour();
	void deal_with(Child* another_child);
};

#endif