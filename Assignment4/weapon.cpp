#include "weapon.h"
#include <cstdlib>
#include <iostream>

Weapon::Weapon(std::string _model, double _power, double _effective_bord, double _hiring_price){
	model=_model;
	if(_power < 0){
		std::cout<<"illegal power" << std::endl;
		abort();
	}
	power=_power;
	if(_effective_bord < 0){
		std::cout<<"illegal effective bord" << std::endl;
		abort();
	}
	effective_bord=_effective_bord;
	if(_hiring_price < 0){
		std::cout<<"illegal hiring price" << std::endl;
		abort();
	}
	hiring_price=_hiring_price;
}
std::string Weapon::get_model(){
	return model;
}
double Weapon::get_power(){
	return power;
}
double Weapon::get_effective_bord(){
	return effective_bord;
}
double Weapon::get_hiring_price(){
	return hiring_price;
}