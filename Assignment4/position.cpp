#include "position.h"

//Getters:
int Position::get_row(){
	return row;
}
int Position::get_col(){
	return col;
}
char Position::get_direction(){
	return direction;
}

//Setters:
void Position::set_row(int _row){
	if(_row >= 0)
		row = _row;
} 
void Position::set_col(int _col){
	if(_col >= 0)
		col = _col;
}
void Position::set_direction(char _direction){
	if(_direction == NORTH || _direction == SOUTH || _direction == EAST || _direction == WEST)
		direction = _direction;
}