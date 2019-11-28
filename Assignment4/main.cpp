#include <iostream>
#include <string>

#include "game.h"

using namespace std;

int main(){
	Game tournoment;
	tournoment.get_players_info();
	tournoment.get_weapons_info();
	tournoment.manage_tournoment();
	tournoment.smart_score_pannel();
	return 0;
}
