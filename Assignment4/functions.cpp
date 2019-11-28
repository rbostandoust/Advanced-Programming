#include "header.h"
#include <cmath>
#include <cstdlib>

std::string get_full_name(std::stringstream& ss,char delimetere){
	std::string result="",temp;
	ss >> temp;
	do{
		result+=temp;
		if(result[result.size()-1]==delimetere || temp == "")
			break;
		result+=" ";
		//std::cout<<"\t\t\t\temp:"<<temp<<", result:"<<result<<std::endl;
	}while(ss.peek() != delimetere && ss >> temp);
	if (ss.peek() == delimetere)
    	ss.ignore();
    while(result[result.size()-1] == delimetere || result[result.size()-1] == ' ')
    	result.erase(result.begin()+result.size()-1);
    return result;
}

int get_int_number(std::stringstream& ss,char delimetere){
	int result;
	ss>>result;
    if (ss.peek() == delimetere)
        ss.ignore();
    return result;
}

double get_double_number(std::stringstream& ss,char delimetere){
	double result;
	ss>>result;
    if (ss.peek() == delimetere)
        ss.ignore();
    return result;
}

void increase_index(int& index, int max_index){
	index++;
	if(index == max_index)
		index=0;
}

void initialize_delta(int& dx, int& dy ,char direction){
	switch(direction){
		case NORTH:
			dy=1;
			break;
		case SOUTH:
			dy=-1;
			break;
		case EAST:
			dx=1;
			break;
		case WEST:
			dx=-1;
	}
}

double effectivity(int col_1,int row_1,int col_2,int row_2,double effective_bord){
	double distance = sqrt(pow(col_2 - col_1,2) + pow(row_2 - row_1,2));
	if(distance <= effective_bord)
		return 1;
	if(distance <= 2*effective_bord)
		return 0.5;
	return 0.25;
}

int error_in_shoot(int accuracy){
	int random = rand()%((100-accuracy)*2 + 1) - (100-accuracy); // (accuracy-100) <= random <= (100-accuracy)
	int abs_random = std::abs(random);
	if(abs_random >=0 && abs_random <= 15 - accuracy/10)
		return 0;
	if(abs_random <= floor(pow(52-accuracy/2, 1.1)))
		return random > 0 ? 1 : -1;
	return random > 0 ? 2 : -2;
}

int bullet_in_position(Position* goal,int bullet_col,int bullet_row){
	int dx=0,dy=0;
	char direction = goal->get_direction();
	int gaol_col = goal->get_col();
	int goal_row = goal->get_row();
	initialize_delta(dx,dy,direction);
	if(bullet_col == gaol_col && bullet_row == goal_row)
		return HEAD;
	if(bullet_col == gaol_col+dx && bullet_row == goal_row+dy)
		return CHEST;
	if(bullet_col == gaol_col+2*dx && bullet_row == goal_row+2*dy)
		return ABDOMEN;
	if((bullet_col == gaol_col+dx+dy && bullet_row == goal_row+dy+dx) ||
		(bullet_col == gaol_col+dx-dy && bullet_row == goal_row+dy-dx))
		return ARMS;
	if((bullet_col == gaol_col+3*dx+dy && bullet_row == goal_row+3*dy+dx) ||
		(bullet_col == gaol_col+3*dx-dy && bullet_row == goal_row+3*dy-dx))
		return FEET;
	return 0;
}