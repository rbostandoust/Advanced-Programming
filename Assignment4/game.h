#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <sstream>
#include "player.h"
#include "weapon.h"
#include "position.h"
#include "sponsor.h"
#include "header.h"

#define NO_GAME 0
#define INITITAION 1
#define PREPRATION 2
#define ACTIVE_GAME 3

#define HEAD 5
#define CHEST 3
#define ABDOMEN 2
#define ARMS 1
#define FEET 1
#define ARMS_OR_FEET 1

#define NORMALL_FINISH 0
#define NEWGAME_FINISH 1
#define ENDTOURNAMENT_FINISH 2

class Game
{
public:
	//Game();
	void get_players_info();
	void print_players();
	void get_weapons_info();
	void print_weapons();
	int return_index_of_player_by_id(int id);
	void manage_tournoment();
	void initiate_new_game();
	void sponsorship(std::stringstream& ss);
	void weapon_purchase(std::stringstream& ss);
	int start_game();
	void shoot(std::stringstream& ss, int player_index);
	bool is_game_finished();
	void report_result();
	void do_final_registration();
	void clean_remained_data();
	void smart_score_pannel();
	void show_capital(int num, std::string state);
	void show_kills(int num, std::string state);
	void show_deaths(int num, std::string state);
private:
	std::vector <Player*> players;
	std::vector <Weapon*> weapons; 
	double participation_fee;
	double ticket_revenue;
	std::vector <int> round_index;
};

#endif