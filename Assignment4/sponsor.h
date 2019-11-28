#ifndef __SPONSOR_H__
#define __SPONSOR_H__

class Sponsor
{
public:
	Sponsor(int id,double money);
	int get_supporter_id();
	double get_supporter_money();
private:
	int supporter_id;
	double supporter_money;
};

#endif