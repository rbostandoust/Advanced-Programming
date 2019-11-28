#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include <vector>
#include "position.h"
#include "sponsor.h"
#include "weapon.h"

class Player
{
public:
	Player(int _id, std::string _name, int _accuracy, double _investment);
	int get_id();
	std::string get_name();
	int get_accuracy();
	double get_investment();
	bool is_participate();
	double get_health();
	Position* get_player_pos();
	bool has_sponsor();
	std::vector <Sponsor*> get_sponsors();
	bool has_weapon();
	Weapon* get_weapon();
	int get_num_of_kills();
	int get_num_of_deaths();

	void add_investment(double amount);
	void set_participation(bool status);
	void set_health(double _health);
	void set_player_pos(int row, int col, char direction);
	void set_sponsor_status(bool status);
	void add_sponsor(Sponsor new_sponsor, bool clear_vector=false);
	void set_weapon_status(bool status);
	void add_weapon(Weapon new_weapon);
	void add_num_of_kills();
	void add_num_of_deaths();
private:
	int id;
	std::string name;
	int accuracy;
	double investment;
	bool participation_status;
	double health;
	Position* player_pos;
	bool sponsor_status;
	std::vector <Sponsor*> sponsors;
	bool weapon_status;
	Weapon* player_weapon;
	int num_of_kills;
	int num_of_deaths;
};

#endif