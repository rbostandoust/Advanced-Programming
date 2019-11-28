#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

#include "mad_house.h"
#include "yard.h"
#include "child.h"
#include "peaceful.h"
#include "angry.h"
#include "coward.h"

int main(int argc, char const *argv[])
{
	int dt, T;
	dt = atoi(argv[1]);
	T = atoi(argv[2]);
	MadHouse gholam_yard;
	gholam_yard.get_inputs();
	gholam_yard.simulate(T, dt);
	gholam_yard.clear_memory();
	return 0;
}
