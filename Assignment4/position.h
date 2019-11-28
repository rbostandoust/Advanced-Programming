#ifndef __POSITION_H__
#define __POSITION_H__

#define NORTH 'N'
#define SOUTH 'S'
#define EAST 'E' 
#define WEST 'W'

class Position
{
public:
	int get_row();
	int get_col();
	char get_direction();
	void set_row(int _row);
	void set_col(int _col);
	void set_direction(char _direction);	
private:
	int row;
	int col;
	char direction;
};

#endif