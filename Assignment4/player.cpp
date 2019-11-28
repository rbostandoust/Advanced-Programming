#include "player.h"
#include <cstdlib>
#include <iostream>

Player::Player(int _id, std::string _name, int _accuracy, double _investment){
	id=_id;
	name=_name;
	if(_accuracy%10!=0 || _accuracy <= 0 || _accuracy > 100){
		std::cout<<"illegal accuracy" << std::endl;
		abort();
	}
	accuracy=_accuracy;
	if(investment<0){
		std::cout<<"illegal investment" << std::endl;
		abort();
	}
	investment=_investment;
	participation_status=false;
	player_pos= new Position();
	sponsor_status = false;
	weapon_status = false;
	num_of_kills = 0;
	num_of_deaths = 0;
}

//Getters:
int Player::get_id(){
	return id;
}
std::string Player::get_name(){
	return name;
}
int Player::get_accuracy(){
	return accuracy;
}
double Player::get_investment(){
	return investment;
}
bool Player::is_participate(){
	return participation_status;
}
double Player::get_health(){
	return health;
}
Position* Player::get_player_pos(){
	return player_pos;
}
bool Player::has_sponsor(){
	return sponsor_status;
}
std::vector<Sponsor*> Player::get_sponsors(){
	return sponsors;
}
bool Player::has_weapon(){
	return weapon_status;
}
Weapon* Player::get_weapon(){
	return player_weapon;
}
int Player::get_num_of_kills(){
	return num_of_kills;
}
int Player::get_num_of_deaths(){
	return num_of_deaths;
}

//Setters:
void Player::add_investment(double amount){
	investment += amount;
	if(investment < 0)
		investment = 0;
}
void Player::set_participation(bool status){
	participation_status = status;
}
void Player::set_health(double _health){
	if(_health<0)
		_health=0;
	health = _health;
}
void Player::set_player_pos(int row, int col, char direction){
	player_pos->set_row(row);
	player_pos->set_col(col);
	player_pos->set_direction(direction);
}
void Player::set_sponsor_status(bool status){
	sponsor_status = status;
}
void Player::add_sponsor(Sponsor new_sponsor, bool clear_vector){
	if(clear_vector){
		sponsors.clear();
		return;
	}
	sponsors.push_back(new Sponsor(new_sponsor.get_supporter_id(), new_sponsor.get_supporter_money()) );
}
void Player::set_weapon_status(bool status){
	weapon_status = status;
}
void Player::add_weapon(Weapon new_weapon){
	player_weapon = new Weapon(new_weapon.get_model(), new_weapon.get_power(),
		new_weapon.get_effective_bord(), new_weapon.get_hiring_price());
}
void Player::add_num_of_kills(){
	num_of_kills++;
}
void Player::add_num_of_deaths(){
	num_of_deaths++;
}