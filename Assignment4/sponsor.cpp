#include "sponsor.h"

Sponsor::Sponsor(int id, double money){
	supporter_id = id;
	supporter_money = money;
}
int Sponsor::get_supporter_id(){
	return supporter_id;
}
double Sponsor::get_supporter_money(){
	return supporter_money;
}