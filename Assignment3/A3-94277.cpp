#include "rsdl.h"
#include <string>
#include <vector>
#include <cmath>

#define EMPTY_SPACE 'w'
#define START 's'
#define END 'e'
#define REWARD 'x'
#define BARRIER 'b'
#define TRAP 't'
#define SQUARE_SIZE 60
#define GRAVITY 9.8
#define RIGHT_CUBE 1
#define LEFT_CUBE -1
#define UP_CUBE -1
#define DOWN_CUBE 1
#define INACTIVE_CUBE 0
#define ACTIVE_CUBE 1
#define THROWN_CUBE 2
#define VICTORY 1
#define DEFEAT 2

const int STEP = 5;
const int DELAY_TIME = 10;

struct Point
{
	double x,y;
};

struct Game
{
	string world_name;
	int sugar_cub_limit;
	int rewards_count;
	int start_point_left, start_point_top;
	int end_point_left, end_point_top;
	int width, height;
	vector<string> map;
	vector<Point> rewards_location;
};

int handle_game(window& w,Game& game);
Game get_input();
void highlight_rewards_location(vector<Point>& rewards_location,int row,string line);
void draw_map(window& w,vector<string>& map);
void move(window& w,vector<string>& map,Point& ghande_asal,string direction,vector<Point>& cube,int cube_status,vector<Point>& rewards_location);
bool is_next_x_step_legal(vector<string>& map,Point ghande_asal,int step);
bool is_next_y_step_legal(vector<string>& map,Point ghande_asal,int delta_y,double& v0,double& t,char block=BARRIER);
bool is_ghandeasal_fallen(vector<string>& map,Point ghande_asal,vector<Point>& cube,int cube_status);
void fell_down(window& w,vector<string>& map,Point& ghande_asal,vector<Point>& cube,Point end_point,int cube_status,vector<Point>& rewards_location);
void jump(window& w,vector<string>& map,Point& ghande_asal,string direction,vector<Point>& cube,Point end_point,int cube_status, vector<Point>& rewards_location);
vector<Point> make_box(window& w,vector<string>& map,Point& ghande_asal,int& cube_num);
void make_cube(window& w,vector<string>& map,Point& ghande_asal,vector<Point>& cube,int x_dir,int y_dir,int& cube_num);
bool is_cube_valid(window& w,vector<string>& map,Point& ghande_asal,vector<Point>& cube,double new_x,double new_y,int& cube_num);
bool is_next_x_cube_step_legal(vector<string>& map,int step,vector<Point>& cube,int cube_status);
bool is_next_y_cube_step_legal(vector<string>& map,vector<Point>& cube,int delta_y,double& v0,double& t,int cube_status,char block=BARRIER);
void clear_cubes(window& w,vector<Point>& cube,int& cube_num);
void fix_the_end_of_movement(window& w,vector<string>& map,Point& ghande_asal,vector<Point>& cube,string address,int cube_status,int just_cube=false);
void transfer_to_head_of_cubes(window& w,Point& ghande_asal,vector<Point>& cube,int& cube_num);
void throw_cubes(window& w,vector<string>& map,Point& ghande_asal,string direction,vector<Point>& cube);
bool is_next_y_step_not_cube(Point ghande_asal,vector<Point>& cube,int delta_y,int delta_x,double& v0,double& t,int cube_status);
bool is_next_x_step_not_cube(Point ghande_asal,vector<Point>& cube,int delta_y,int delta_x,int cube_status);
bool is_between(double ghande_asal,double cube);
int is_game_finished(Point ghande_asal, vector<string>& map, Point end_point);
bool has_colision(Point first,Point second);
void handle_rewards(window& w,Point ghande_asal,vector<Point>& rewards_location);
void edit_map(window& w,Point end_point,vector<Point>& rewards_location,vector<Point>& cube);
void end_game(int game_status,window& w,Game& game);
void loose(window& w,int width,int height);
void victory(window& w,int width,int height,int score,bool is_complete);

int main()
{
	Game game;
	game=get_input();
	window w(SQUARE_SIZE*game.width,SQUARE_SIZE*game.height);
	int game_status = handle_game(w,game);
	end_game(game_status,w,game);
	return 0;
}

int handle_game(window& w,Game& game){
	Point ghande_asal,end_point;
	ghande_asal.x = game.start_point_left*SQUARE_SIZE;
	ghande_asal.y = game.start_point_top*SQUARE_SIZE;
	end_point.x = game.end_point_left*SQUARE_SIZE;
	end_point.y = game.end_point_top*SQUARE_SIZE;

	draw_map(w,game.map);
	bool quit=false;
	vector <Point> cube;
	int cube_status=INACTIVE_CUBE;
	int game_status=0;
	while(!quit){
		HANDLE({
			KEY_PRESS(RIGHT,{move(w,game.map,ghande_asal,"right",cube,cube_status,game.rewards_location);});
			KEY_PRESS(LEFT,{move(w,game.map,ghande_asal,"left",cube,cube_status,game.rewards_location);})
			KEY_PRESS(UP,{jump(w,game.map,ghande_asal,"",cube,end_point,cube_status,game.rewards_location);})
			KEY_PRESS(e,{jump(w,game.map,ghande_asal,"right",cube,end_point,cube_status,game.rewards_location);})
			KEY_PRESS(q,{jump(w,game.map,ghande_asal,"left",cube,end_point,cube_status,game.rewards_location);})
			KEY_PRESS(LCTRL,{
				clear_cubes(w,cube,game.sugar_cub_limit);
				cube= make_box(w,game.map,ghande_asal,game.sugar_cub_limit);
				if(cube.size()>0)
					cube_status = ACTIVE_CUBE;
				else
					cube_status = INACTIVE_CUBE;
			})
			KEY_PRESS(SPACE,{
				if(cube_status == ACTIVE_CUBE){
					transfer_to_head_of_cubes(w,ghande_asal,cube,game.sugar_cub_limit);
					handle_rewards(w,ghande_asal,game.rewards_location);
					cube_status=0;
				}
			})
			KEY_PRESS(c,{
				if(cube_status == ACTIVE_CUBE){
					cube_status = THROWN_CUBE;
					throw_cubes(w,game.map,ghande_asal,"right",cube);
				}
			})
			KEY_PRESS(z,{
				if(cube_status == ACTIVE_CUBE){
					cube_status = THROWN_CUBE;
					throw_cubes(w,game.map,ghande_asal,"left",cube);
				}
			})
			if(game_status = is_game_finished(ghande_asal,game.map,end_point))
				quit=true;
			if(is_ghandeasal_fallen(game.map,ghande_asal,cube,cube_status))
				fell_down(w,game.map,ghande_asal,cube,end_point,cube_status,game.rewards_location);
			edit_map(w,end_point,game.rewards_location,cube);
			QUIT(quit=true);
			w.update_screen();
		});
	}
	return game_status;
}
Game get_input(){
	Game temp;
	cin>> temp.world_name;
	cin>> temp.sugar_cub_limit;
	cin>> temp.rewards_count;
	cin>> temp.start_point_left >> temp.start_point_top;
	cin>> temp.end_point_left >> temp.end_point_top;
	cin>> temp.width >> temp.height;
	string line;
	while(cin>>line){
		temp.map.push_back(line);
		highlight_rewards_location(temp.rewards_location,temp.map.size()-1,line);
	}
	return temp;
}
void highlight_rewards_location(vector<Point>& rewards_location,int row,string line){
	for (int i = 0; i < line.length(); i++)
	{
		if(line[i]==REWARD){
			rewards_location.push_back(Point());
			rewards_location[rewards_location.size()-1].x=i*SQUARE_SIZE;
			rewards_location[rewards_location.size()-1].y=row*SQUARE_SIZE;	
		}
	}
}
void draw_map(window& w,vector<string>& map){
	for(int i=0;i<map.size();i++)
		for (int j = 0; j < map[0].length(); j++)
			switch(map[i][j]){
				case EMPTY_SPACE:
					break;
				case START:
					w.draw_bmp("images/right/bmp_60/00.bmp",j*SQUARE_SIZE,i*SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
					break;
				case END:
					w.draw_bmp("images/door/bmp_60/00.bmp",j*SQUARE_SIZE,i*SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
					break;
				case REWARD:
					w.draw_bmp("images/crown/bmp_60/00.bmp",j*SQUARE_SIZE,i*SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
					break;
				case BARRIER:
					w.fill_rect(j*SQUARE_SIZE,i*SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE,BLACK);
					break;
				case TRAP:
					w.draw_bmp("images/trap/bmp_60/t2.bmp",j*SQUARE_SIZE,i*SQUARE_SIZE,SQUARE_SIZE,SQUARE_SIZE);
					break;
			}
}
void move(window& w,vector<string>& map,Point& ghande_asal,string direction,vector<Point>& cube,int cube_status,vector<Point>& rewards_location){
	string base="images/"+direction+"/bmp_60/";
	string stick_end[12]={
		"00.bmp","01.bmp","02.bmp","03.bmp","04.bmp","05.bmp","06.bmp",
		"07.bmp","08.bmp","09.bmp","10.bmp","11.bmp"/*,"12.bmp"*/
	};
	int step=(direction=="right" ? STEP : - STEP);
	for(int i=0;i<12;i++){
		if(!is_next_x_step_legal(map,ghande_asal,step) || !is_next_x_cube_step_legal(map,step,cube,cube_status)
		 || !is_next_x_step_not_cube(ghande_asal,cube,0,step,cube_status)){
			w.draw_bmp(base+stick_end[0],ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);
			return;
		}
		for (int j = 0; j < cube.size() && cube_status==ACTIVE_CUBE ; j++){
			w.fill_rect(cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
			cube[j].x+=step;
			w.draw_bmp("images/cube/bmp_60/00.bmp",cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE);
		}
		string address=base+stick_end[i];
		w.fill_rect(ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
		ghande_asal.x+=step;
		handle_rewards(w,ghande_asal,rewards_location);
		w.draw_bmp(address,ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);
		w.update_screen();
		DELAY(DELAY_TIME);
	}
}
bool is_next_x_step_legal(vector<string>& map,Point ghande_asal, int step){
	int row=ghande_asal.y/SQUARE_SIZE;
	int col=ghande_asal.x/SQUARE_SIZE;
	int direction=1;
	if(step<0)
		direction=-1;
	if(map[row][col+direction]==BARRIER){
		/*cout<<"col: "<<col<<endl;
		cout<<(col+1)*SQUARE_SIZE<<endl;
		cout<<ghande_asal.x<<endl;*/
		if(step>0)
			if(ghande_asal.x+step>(col)*SQUARE_SIZE)
				return false;
		if(step<0)
			if(ghande_asal.x+step<(col)*SQUARE_SIZE)
				return false;
	}
	row=(SQUARE_SIZE+ghande_asal.y-1)/SQUARE_SIZE;
	if(map[row][col+direction]==BARRIER){
		/*cout<<"col: "<<col<<endl;
		cout<<(col+1)*SQUARE_SIZE<<endl;
		cout<<ghande_asal.x<<endl;*/
		if(step>0)
			if(ghande_asal.x+step>(col)*SQUARE_SIZE)
				return false;
		if(step<0)
			if(ghande_asal.x+step<(col)*SQUARE_SIZE)
				return false;
	}
	return true;
}
bool is_ghandeasal_fallen(vector<string>& map,Point ghande_asal,vector<Point>& cube,int cube_status){
	int row=((int)ghande_asal.y)/SQUARE_SIZE;
	int col=((int)ghande_asal.x)/SQUARE_SIZE;
	if(map[row+1][col]==BARRIER)
		return false;
	else {
		col=(ghande_asal.x+SQUARE_SIZE-1)/SQUARE_SIZE;
		if(map[row+1][col]==BARRIER)
			return false;
		if(cube_status == THROWN_CUBE){
			double temp=0;
			if(!is_next_y_step_not_cube(ghande_asal,cube,5,0,temp,temp,cube_status))
				return false;
		}
		return true;
	}
}
bool is_next_y_step_legal(vector<string>& map,Point ghande_asal,int delta_y,double& v0,double& t,char block){
	int row=int(ghande_asal.y)/SQUARE_SIZE;
	int col=ghande_asal.x/SQUARE_SIZE;
	int direction;
	char block_prime=BARRIER;
	if(block == TRAP)
		block_prime=TRAP;
	if(delta_y>=0)
		direction=1;
	else 
		direction=-1;
	if(direction==-1 && row==0){
		v0=0;
		t=0;
		return true;
	}
	if(direction==1 && row==map.size()-1)
		return false;
	if(map[row+direction][col]==block_prime){
		if(direction==1)
			if(ghande_asal.y+delta_y>=(row)*SQUARE_SIZE)
				return false;
		if(direction==-1)
			if(ghande_asal.y+delta_y<=(row)*SQUARE_SIZE){
				v0=0;
				t=0;
				return true;
			}
	}
	if(ghande_asal.y+delta_y>=(row+1)*SQUARE_SIZE && map[row+2][col]==block_prime)
		return false;
	col=(ghande_asal.x+SQUARE_SIZE-1)/SQUARE_SIZE;
	if(map[row+direction][col]==block_prime){
		if(direction==1)
			if(ghande_asal.y+delta_y>=(row)*SQUARE_SIZE)
				return false;
		if(direction==-1)
			if(ghande_asal.y+delta_y<=(row)*SQUARE_SIZE){
				v0=0;
				t=0;
				return true;
			}
	}
	if(ghande_asal.y+delta_y>=(row+1)*SQUARE_SIZE && map[row+2][col]==block_prime)
		return false;
	if(block==TRAP)
		return is_next_y_step_legal(map,ghande_asal,delta_y,v0,t,BARRIER);
	return true;
}
void fell_down(window& w,vector<string>& map,Point& ghande_asal,vector<Point>& cube,Point end_point,int cube_status,vector<Point>& rewards_location){
	double dt=0.2;
	double t=0;
	double v0=0;
	string address="images/jump/right/bmp_60/00.bmp";
	while(is_next_y_step_legal(map,ghande_asal,GRAVITY*t*dt+1/2*GRAVITY*dt*dt,v0,t) && 
		is_next_y_cube_step_legal(map,cube,GRAVITY*t*dt+1/2*GRAVITY*dt*dt,v0,t,cube_status) &&
		is_next_y_step_not_cube(ghande_asal,cube,GRAVITY*t*dt+1/2*GRAVITY*dt*dt,0,v0,t,cube_status) &&
		!is_game_finished(ghande_asal,map,end_point)){
		for (int j = cube.size()-1; j >= 0 && cube_status== ACTIVE_CUBE; j--){
			w.fill_rect(cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
			cube[j].y+=GRAVITY*t*dt+ 1/2*GRAVITY*dt*dt;
			w.draw_bmp("images/cube/bmp_60/00.bmp",cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE);
		}
		w.fill_rect(ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
		ghande_asal.y+=GRAVITY*t*dt+ 1/2*GRAVITY*dt*dt;
		handle_rewards(w,ghande_asal,rewards_location);
		w.draw_bmp(address,ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);
		DELAY(DELAY_TIME);
		t+=0.2;
		w.update_screen();
	}
	fix_the_end_of_movement(w,map,ghande_asal,cube,address,cube_status);
}
void jump(window& w,vector<string>& map,Point& ghande_asal,string direction,vector<Point>& cube,Point end_point,int cube_status,vector<Point>& rewards_location){
	double dt=0.2;
	double t=0;
	double R=2*SQUARE_SIZE;
	double H=1.5*SQUARE_SIZE;
	double teta=acos(R/sqrt(R*R+16*H*H));
	double v0=sqrt(2*GRAVITY*H/(sin(teta)*sin(teta)));
	int zarib=1;
	if(direction=="left")
		zarib=-1;
	string address="images/jump/"+direction+"/bmp_60/00.bmp";
	if(direction==""){
		address="images/jump/right/bmp_60/00.bmp";
		zarib=0;
	}
	while(is_next_y_step_legal(map,ghande_asal,GRAVITY*t*dt+1/2*GRAVITY*dt*dt - sin(teta)*v0*dt,v0,t) &&
		is_next_y_cube_step_legal(map,cube, GRAVITY*t*dt+1/2*GRAVITY*dt*dt - sin(teta)*v0*dt ,v0,t,cube_status) &&
		is_next_y_step_not_cube(ghande_asal,cube, GRAVITY*t*dt+1/2*GRAVITY*dt*dt - sin(teta)*v0*dt ,zarib*v0*cos(teta)*dt,v0,t,cube_status) &&
		!is_game_finished(ghande_asal,map,end_point)){
		teta=acos(R/sqrt(R*R+16*H*H));
		if(!(is_next_x_step_legal(map,ghande_asal,zarib*v0*cos(teta)*dt)) || 
			!is_next_x_cube_step_legal(map,zarib*v0*cos(teta)*dt,cube,cube_status) ||
			!is_next_x_step_not_cube(ghande_asal,cube, GRAVITY*t*dt+1/2*GRAVITY*dt*dt - sin(teta)*v0*dt , zarib*v0*cos(teta)*dt ,cube_status))
			teta=acos(0);
		for (int j = 0; j < cube.size() && cube_status == ACTIVE_CUBE ; j++){
			w.fill_rect(cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
			cube[j].x+=zarib*v0*cos(teta)*dt;
			cube[j].y+=GRAVITY*t*dt+ 1/2*GRAVITY*dt*dt - v0*dt;
			w.draw_bmp("images/cube/bmp_60/00.bmp",cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE);
		}
		w.fill_rect(ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
		ghande_asal.y+=GRAVITY*t*dt+ 1/2*GRAVITY*dt*dt - v0*dt;
		ghande_asal.x+=zarib*v0*cos(teta)*dt;
		handle_rewards(w,ghande_asal,rewards_location);
		w.draw_bmp(address,ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);
		DELAY(DELAY_TIME*1.2);
		t+=0.2;
		w.update_screen();
	}
	fix_the_end_of_movement(w,map,ghande_asal,cube,address,cube_status);
}
vector<Point> make_box(window& w,vector<string>& map,Point& ghande_asal,int& cube_num){
	vector <Point> cube;
	w.fill_rect(ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
	w.draw_bmp("images/make_box/bmp_60/00.bmp",ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);
	bool quit=false;
	while(!quit){
		HANDLE({
			KEY_PRESS(RIGHT,{quit=true;});
			KEY_PRESS(LEFT,{quit=true;});
			KEY_PRESS(UP,{quit=true;});
			KEY_PRESS(DOWN,{quit=true;});
			KEY_PRESS(e,{quit=true;});
			KEY_PRESS(q,{quit=true;});
			KEY_PRESS(c,{quit=true;});
			KEY_PRESS(z,{quit=true;});
			KEY_PRESS(LCTRL,{quit=true;});
			KEY_PRESS(SPACE,{quit=true;});
			KEY_PRESS(w,{make_cube(w,map,ghande_asal,cube,0,UP_CUBE,cube_num);});
			KEY_PRESS(s,{make_cube(w,map,ghande_asal,cube,0,DOWN_CUBE,cube_num);});
			KEY_PRESS(a,{make_cube(w,map,ghande_asal,cube,LEFT_CUBE,0,cube_num);});
			KEY_PRESS(d,{make_cube(w,map,ghande_asal,cube,RIGHT_CUBE,0,cube_num);});
			w.update_screen();
		});
	}
	w.draw_bmp("images/right/bmp_60/00.bmp",ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);
	return cube;
}
void make_cube(window& w,vector<string>& map,Point& ghande_asal,vector<Point>& cube,int x_dir,int y_dir,int& cube_num){
	double row,col;
	if(cube.size()==0){
		row=ghande_asal.y;
		col=ghande_asal.x;
	}
	else{
		row=cube[cube.size()-1].y;
		col=cube[cube.size()-1].x;
	}
	if(is_cube_valid(w,map,ghande_asal,cube,col+x_dir*SQUARE_SIZE,row+y_dir*SQUARE_SIZE,cube_num) && cube_num>0){
		Point temp;
		temp.y=row + y_dir*SQUARE_SIZE;
		temp.x=col + x_dir*SQUARE_SIZE;
		cube.push_back(temp);
		cube_num--;
		w.draw_bmp("images/cube/bmp_60/00.bmp",cube[cube.size()-1].x,cube[cube.size()-1].y,SQUARE_SIZE,SQUARE_SIZE);
	}
}
bool is_cube_valid(window& w,vector<string>& map,Point& ghande_asal,vector<Point>& cube,double new_x,double new_y,int& cube_num){
	if(map[(new_y)/SQUARE_SIZE][(new_x)/SQUARE_SIZE]==BARRIER || map[(new_y)/SQUARE_SIZE][(new_x)/SQUARE_SIZE]==TRAP)
		return false;
	if(cube.size()>=2){
		if(new_x==cube[cube.size()-2].x && new_y==cube[cube.size()-2].y){
			w.fill_rect(cube[cube.size()-1].x,cube[cube.size()-1].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
			cube.pop_back();
			cube_num++;
			return false;
		}
	}
	if(cube.size()==1){
		if(new_x==ghande_asal.x && new_y==ghande_asal.y){
			w.fill_rect(cube[0].x,cube[0].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
			cube.pop_back();
			cube_num++;
			return false;
		}
	}
	for(int i=0;i<cube.size();i++)
		if(new_y==cube[i].y && new_x==cube[i].x)
			return false;
	if(new_y==ghande_asal.y && new_x==ghande_asal.x)
		return false;
	//checking the right side;
	double new_x_prime=new_x+SQUARE_SIZE-2;
	double new_y_prime=new_y+SQUARE_SIZE-2;
	if(map[(new_y_prime)/SQUARE_SIZE][(new_x_prime)/SQUARE_SIZE]==BARRIER ||
		 map[(new_y_prime)/SQUARE_SIZE][(new_x_prime)/SQUARE_SIZE]==TRAP)
		return false;
	return true;
}
bool is_next_x_cube_step_legal(vector<string>& map,int step,vector<Point>& cube,int cube_status){
	if(cube_status != ACTIVE_CUBE )
		return true;
	for(int i=0;i<cube.size();i++){
		if(!is_next_x_step_legal(map,cube[i],step))
			return false;
	}
	return true;
}
bool is_next_y_cube_step_legal(vector<string>& map,vector<Point>& cube,int delta_y,double& v0,double& t,int cube_status,char block){
	if(cube_status != ACTIVE_CUBE )
		return true;
	for(int i=0;i<cube.size();i++){
		if(!is_next_y_step_legal(map,cube[i],delta_y,v0,t,block))
			return false;
	}
	return true;
}
void clear_cubes(window& w,vector<Point>& cube,int& cube_num){
	for (int i = 0; i < cube.size(); i++)
		w.fill_rect(cube[i].x,cube[i].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
	cube_num+=cube.size();
	cube.clear();
}
void fix_the_end_of_movement(window& w,vector<string>& map,Point& ghande_asal,vector<Point>& cube,string address,int cube_status,int just_cube){
	int y_round,extra=0;
	y_round = (just_cube ? (int)cube[0].y : (int)ghande_asal.y);
	string s0="00",s1="01";
	string cube_address="images/cube/bmp_60/"+ (just_cube ? s1 : s0) +".bmp";
	if(y_round%SQUARE_SIZE!=0)
		extra=SQUARE_SIZE - y_round % SQUARE_SIZE;
	for (int j=0;j< cube.size() && (cube_status== ACTIVE_CUBE || (cube_status== THROWN_CUBE &&just_cube)) ;j++){
			w.fill_rect(cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
			if(j!=0)
				w.draw_bmp(cube_address,cube[j-1].x,cube[j-1].y,SQUARE_SIZE,SQUARE_SIZE);
			cube[j].y +=extra;
			w.draw_bmp(cube_address,cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE);
	}
	if(!just_cube){
		w.fill_rect(ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
		if(cube.size()>=1 && cube_status== ACTIVE_CUBE)
			w.draw_bmp(cube_address,cube[0].x,cube[0].y,SQUARE_SIZE,SQUARE_SIZE);
		ghande_asal.y +=extra;
		w.draw_bmp(address,ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);
	}
}
void transfer_to_head_of_cubes(window& w,Point& ghande_asal,vector<Point>& cube,int& cube_num){
	if(cube.size()==0)
		return;
	w.fill_rect(ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
	ghande_asal.x=cube[cube.size()-1].x;
	ghande_asal.y=cube[cube.size()-1].y;
	clear_cubes(w,cube,cube_num);
	w.draw_bmp("images/right/bmp_60/00.bmp",ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);
}
void throw_cubes(window& w,vector<string>& map,Point& ghande_asal,string direction,vector<Point>& cube){
	double dt=0.2;
	double t=0;
	double R=2*SQUARE_SIZE;
	double H=1.5*SQUARE_SIZE;
	double teta=acos(R/sqrt(R*R+16*H*H));
	double v0=sqrt(2*GRAVITY*H/(sin(teta)*sin(teta)));
	int zarib=1;
	if(direction=="left")
		zarib=-1;
	string address="images/cube/bmp_60/00.bmp";
	while(is_next_y_cube_step_legal(map,cube,GRAVITY*t*dt+1/2*GRAVITY*dt*dt - sin(teta)*v0*dt,v0,t,1,TRAP)){
		teta=acos(R/sqrt(R*R+16*H*H));
		if(!is_next_x_cube_step_legal(map,zarib*v0*cos(teta)*dt,cube,1))
			teta=acos(0);
		for (int j = 0; j < cube.size(); j++){
			w.fill_rect(cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
			cube[j].x+=zarib*v0*cos(teta)*dt;
			cube[j].y+=GRAVITY*t*dt+ 1/2*GRAVITY*dt*dt - v0*dt;
			w.draw_bmp("images/cube/bmp_60/00.bmp",cube[j].x,cube[j].y,SQUARE_SIZE,SQUARE_SIZE);
		}
		DELAY(DELAY_TIME*1.2);
		t+=0.2;
		w.update_screen();
	}
	fix_the_end_of_movement(w,map,ghande_asal,cube,address,2,true);
	w.draw_bmp("images/jump/"+direction+"/bmp_60/00.bmp",ghande_asal.x,ghande_asal.y,SQUARE_SIZE,SQUARE_SIZE);	
}
bool is_next_y_step_not_cube(Point ghande_asal,vector<Point>& cube,int delta_y,int delta_x,double& v0,double& t,int cube_status){
	if(cube_status == THROWN_CUBE){
		for (int i = 0; i < cube.size(); i++)
		{
			bool is_ghandeasal_between = is_between(ghande_asal.x,cube[i].x);
			if((ghande_asal.y >= cube[i].y + SQUARE_SIZE && ghande_asal.y + delta_y <= cube[i].y + SQUARE_SIZE) && (is_ghandeasal_between)){
				v0=0;
				t=0;
				return true;
			} 
			if((ghande_asal.y + SQUARE_SIZE -1 <= cube[i].y && ghande_asal.y + delta_y + SQUARE_SIZE >= cube[i].y) && (is_ghandeasal_between))
				return false;
			is_ghandeasal_between = is_between(ghande_asal.x + SQUARE_SIZE -1,cube[i].x);
			if((ghande_asal.y >= cube[i].y + SQUARE_SIZE && ghande_asal.y + delta_y <= cube[i].y + SQUARE_SIZE) && (is_ghandeasal_between)){
				v0=0;
				t=0;
				return true;
			} 
			if((ghande_asal.y + SQUARE_SIZE -1 <= cube[i].y && ghande_asal.y + delta_y + SQUARE_SIZE >= cube[i].y) && (is_ghandeasal_between))
				return false;
		}
	}
	return true;
}
bool is_next_x_step_not_cube(Point ghande_asal,vector<Point>& cube,int delta_y,int delta_x,int cube_status){
	if(cube_status == THROWN_CUBE){
		for (int i = 0; i < cube.size(); i++)
		{
			bool is_ghandeasal_between = is_between(ghande_asal.y,cube[i].y);
			if((ghande_asal.x >= cube[i].x + SQUARE_SIZE && ghande_asal.x + delta_x <= cube[i].x + SQUARE_SIZE) && is_ghandeasal_between)
				return false;
			if((ghande_asal.x + SQUARE_SIZE <= cube[i].x && ghande_asal.x + delta_x + SQUARE_SIZE >= cube[i].x) && is_ghandeasal_between)
				return false;
			is_ghandeasal_between = is_between(ghande_asal.y+SQUARE_SIZE-1,cube[i].y);
			if((ghande_asal.x >= cube[i].x + SQUARE_SIZE && ghande_asal.x + delta_x <= cube[i].x + SQUARE_SIZE) && is_ghandeasal_between)
				return false;
			if((ghande_asal.x + SQUARE_SIZE <= cube[i].x && ghande_asal.x + delta_x + SQUARE_SIZE >= cube[i].x) && is_ghandeasal_between)
				return false;
		}
	}
	return true;
}
bool is_between(double ghande_asal,double cube){
	if(ghande_asal  >= (int)cube && ghande_asal <= (int)cube +SQUARE_SIZE)
		return true;
	return false;
}
int is_game_finished(Point ghande_asal, vector<string>& map, Point end_point){
	if(has_colision(ghande_asal,end_point))
		return VICTORY;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].length(); j++)
		{
			if(map[i][j] == TRAP){
				Point temp={j*SQUARE_SIZE,i*SQUARE_SIZE};
				if(has_colision(ghande_asal,temp))
					return DEFEAT;
			}
		}
	}
	return false;
}
bool has_colision(Point first,Point second){
	if( (is_between(first.x+2 ,second.x) && is_between(first.y+2,second.y)) || 
		(is_between(first.x + SQUARE_SIZE-2,second.x) && is_between(first.y+2,second.y)) ||
		(is_between(first.x+2 ,second.x) && is_between(first.y + SQUARE_SIZE-2,second.y)) ||
		(is_between(first.x + SQUARE_SIZE-2,second.x) && is_between(first.y + SQUARE_SIZE-2,second.y)))
		return true;
	return false;
}
void handle_rewards(window& w,Point ghande_asal,vector<Point>& rewards_location){
	for (int i = 0; i < rewards_location.size(); i++)
	{
		if(has_colision(ghande_asal,rewards_location[i])){
			w.fill_rect(rewards_location[i].x,rewards_location[i].y,SQUARE_SIZE,SQUARE_SIZE,WHITE);
			rewards_location.erase(rewards_location.begin()+i);
		}
	}
}
void edit_map(window& w,Point end_point,vector<Point>& rewards_location,vector<Point>& cube){
	int flag=0;
	for(int i=0; i < cube.size(); i++){
		if(has_colision(cube[i],end_point))
			flag=1;
	}
	if(flag==0)
		w.draw_bmp("images/door/bmp_60/00.bmp",end_point.x,end_point.y,SQUARE_SIZE,SQUARE_SIZE);
	for (int j = 0; j < rewards_location.size(); j++)
	{
		flag=0;
		for(int i=0; i < cube.size(); i++)
			if(has_colision(cube[i],rewards_location[j]))
				flag=1;
		if(flag==0)
			w.draw_bmp("images/crown/bmp_60/00.bmp",rewards_location[j].x,rewards_location[j].y,SQUARE_SIZE,SQUARE_SIZE);
	}
}
void end_game(int game_status,window& w,Game& game){
	if(game_status == 0)
		return;
	else if(game_status == VICTORY){
		bool is_complete=false;
		int score = game.rewards_count - game.rewards_location.size();
		if(game.rewards_location.size()==0)
			is_complete=true;
		victory(w,SQUARE_SIZE*game.width,SQUARE_SIZE*game.height,score,is_complete);
	}
	else if(game_status == DEFEAT)
		loose(w,SQUARE_SIZE*game.width,SQUARE_SIZE*game.height);
	bool quit=false;
	while(!quit){
		HANDLE(QUIT(quit=true));
	}
}
void loose(window& w,int width,int height){
	for(int i=0;i<height/SQUARE_SIZE;i+=2){
		w.fill_rect(0,i*SQUARE_SIZE,width,SQUARE_SIZE,RED);
		w.update_screen();
		DELAY(200);
	}
	for(int i=1;i<height/SQUARE_SIZE;i+=2){
		w.fill_rect(0,i*SQUARE_SIZE,width,SQUARE_SIZE,RGB(125,0,0));
		w.update_screen();
		DELAY(200);
	}
	w.draw_transparent_bmp("images/game_over.bmp",(width/2)-180,height/2-85,RED);
	w.update_screen();
}
void victory(window& w,int width,int height,int score,bool is_complete){
	for(int i=0;i<height/SQUARE_SIZE;i+=2){
		w.fill_rect(0,i*SQUARE_SIZE,width,SQUARE_SIZE,GREEN);
		w.update_screen();
		DELAY(200);
	}
	for(int i=1;i<height/SQUARE_SIZE;i+=2){
		w.fill_rect(0,i*SQUARE_SIZE,width,SQUARE_SIZE,RGB(0,125,0));
		w.update_screen();
		DELAY(200);
	}
	string end[10]={"0.bmp","1.bmp","2.bmp","3.bmp","4.bmp",
		"5.bmp","6.bmp","7.bmp","8.bmp","9.bmp"};
	string base="images/score/";
	w.draw_transparent_bmp("images/game_score.bmp",(width/2)-200, height/2-80-60,GREEN);
	w.draw_transparent_bmp(base + end[score] ,(width/2) + 92, height/2-90,GREEN);
	if(is_complete)
		w.draw_transparent_bmp("images/congradution.bmp",(width/2)-180,height/2-80,GREEN);
	else
		w.draw_transparent_bmp("images/incomplete.bmp",(width/2)-210,height/2-80,RED);
	w.update_screen();
}
