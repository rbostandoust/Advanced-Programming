#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <string>

class Weapon
{
public:
	Weapon(std::string _model, double _power, double _effective_bord, double _hiring_price);
	std::string get_model();
	double get_power();
	double	get_effective_bord();
	double get_hiring_price();
private:
	std::string model;
	double power;
	double effective_bord;
	double hiring_price;
};

#endif