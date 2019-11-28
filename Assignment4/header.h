#ifndef __header_h__ 
#define __header_h__

#include <string>
#include <sstream>
#include <iostream>
#include "game.h"

std::string get_full_name(std::stringstream& ss,char delimetere);
int get_int_number(std::stringstream& ss,char delimetere);
double get_double_number(std::stringstream& ss,char delimetere);
void increase_index(int& index, int max_index);
void initialize_delta(int& dx, int& dy ,char direction);
double effectivity(int col_1,int row_1,int col_2,int row_2,double effective_bord);
int error_in_shoot(int accuracy);
int bullet_in_position(Position* goal,int bullet_col,int bullet_row);

#endif 