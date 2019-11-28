#include <iostream>
#include <vector>

#define EMPTY '0'
#define PEG '1'
#define DOWN 'D'
#define UP 'U'
#define RIGHT 'R'
#define LEFT 'L'

using namespace std;

vector<string> get_inputs();
void print_wall(vector<string>& board);
void tile_the_whole_wall(int row,vector<string>& board,int& num_of_vertics,int& max);
char check_possibility(int row,int col,vector<string>& board);
int remain_blocks(vector<string>& wall);
void tile_the_wall(int row,int col,vector<string>& board,char type,bool write_command,int& num_of_vertics);

bool down_possible(int row,int col,vector<string>& board);
bool up_possible(int row,int col,vector<string>& board);
bool right_possible(int row,int col,vector<string>& board);
bool left_possible(int row,int col,vector<string>& board);
void tile_down(int row,int col,vector<string>& board,char tile);
void tile_up(int row,int col,vector<string>& board,char tile);
void tile_right(int row,int col,vector<string>& board,char tile);
void tile_left(int row,int col,vector<string>& board,char tile);

int main(){
	vector<string> wall=get_inputs();
	int num_of_vertics=0,max=-1;
	if(remain_blocks(wall)%4==0){
		tile_the_whole_wall(0,wall,num_of_vertics,max);
	}
	cout<<max<<endl;
	return 0;
}

vector<string> get_inputs(){
	string line;
	vector<string> wall;
	while(true){
		getline(cin,line);
		if(line.length()==0)
			return wall;
		wall.push_back(line);
	}
}
void print_wall(vector<string>& board){
	cout<<endl;
	for (int i = 0; i < board.size(); i++)
		cout<<board[i]<< endl;
}
void tile_the_whole_wall(int row,vector<string>& board,int& num_of_vertics,int& max){
	if(remain_blocks(board)==0){
		print_wall(board);
		if(max<num_of_vertics)
			max=num_of_vertics;
		return;
	}
	char possibile;
	for(int i=row;i<board.size();i++){
		for(int j=0;j<board[0].length();j++){
			if(board[i][j]!=EMPTY)
				continue;
			possibile=check_possibility(i,j,board);
			if(possibile=='0')
				return ;
			tile_the_wall(i,j,board,possibile,true,num_of_vertics);// tile the wall
			// for testing
			//print_wall(board); 
			//cout<<"row: "<<i<<" , col: "<<j<<endl;
			tile_the_whole_wall(i,board,num_of_vertics,max);
			tile_the_wall(i,j,board,possibile,false,num_of_vertics);// untile the wall
		}
	}
	return;
}
char check_possibility(int row,int col,vector<string>& board){
	if(row!=board.size()-1 && col<board[0].length()-2)
		if(down_possible(row,col,board))
			return DOWN;

	if(row!=board.size()-1 && col>0 && col<board[0].length()-1)
		if(up_possible(row,col,board))
			return UP;

	if(col!=board[0].length()-1 && row<board.size()-2)
		if(right_possible(row,col,board))
			return RIGHT;

	if(col!=0 && row<board.size()-2)
		if(left_possible(row,col,board))
			return LEFT;

	return '0';
}
int remain_blocks(vector<string>& wall){
	int counter=0;
	for(int i=0;i<wall.size();i++)
		for (int j = 0; j < wall[0].length(); j++)
			if(wall[i][j]==EMPTY)
				counter++;
	return counter;
}
void tile_the_wall(int row,int col,vector<string>& board,char type,bool write_command,int& num_of_vertics){
	switch(type){
		case DOWN:
			if(write_command){
				tile_down(row,col,board,DOWN);
				num_of_vertics++;
			}
			else{
				tile_down(row,col,board,EMPTY);
				num_of_vertics--;
			}
			break;
		case UP:
			if(write_command){
				tile_up(row,col,board,UP);
				num_of_vertics++;
			}
			else{
				tile_up(row,col,board,EMPTY);
				num_of_vertics--;
			}
			break;
		case RIGHT:
			if(write_command)
				tile_right(row,col,board,RIGHT);
			else
				tile_right(row,col,board,EMPTY);
			break;
		case LEFT:
			if(write_command)
				tile_left(row,col,board,LEFT);
			else
				tile_left(row,col,board,EMPTY);
			break;
	}
}

bool down_possible(int row,int col,vector<string>& board){
	if(board[row][col+1]==EMPTY && board[row][col+2]==EMPTY && board[row+1][col+1]==EMPTY)
		return true;
}
bool up_possible(int row,int col,vector<string>& board){
	if(board[row+1][col-1]==EMPTY && board[row+1][col]==EMPTY && board[row+1][col+1]==EMPTY)
		return true;
}
bool right_possible(int row,int col,vector<string>& board){
	if(board[row+1][col]==EMPTY && board[row+2][col]==EMPTY && board[row+1][col+1]==EMPTY)
		return true;
}
bool left_possible(int row,int col,vector<string>& board){
	if(board[row+1][col]==EMPTY && board[row+2][col]==EMPTY && board[row+1][col-1]==EMPTY)
		return true;
}
void tile_down(int row,int col,vector<string>& board,char tile){
	board[row][col]=tile;
	board[row][col+1]=tile;
	board[row][col+2]=tile;
	board[row+1][col+1]=tile;
}
void tile_up(int row,int col,vector<string>& board,char tile){
	board[row][col]=tile;
	board[row+1][col-1]=tile;
	board[row+1][col]=tile;
	board[row+1][col+1]=tile;
}
void tile_right(int row,int col,vector<string>& board,char tile){
	board[row][col]=tile;
	board[row+1][col]=tile;
	board[row+2][col]=tile;
	board[row+1][col+1]=tile;
}
void tile_left(int row,int col,vector<string>& board,char tile){
	board[row][col]=tile;
	board[row+1][col]=tile;
	board[row+2][col]=tile;
	board[row+1][col-1]=tile;
}