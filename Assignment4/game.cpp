#include <fstream>
#include <iostream>
#include <cstdlib>
#include "game.h"

void Game::get_players_info(){
	std::ifstream input;
	std::string temp_name,line;
	int temp_id,temp_accuracy,temp_investment;
	std::stringstream ss;

	input.open("players.txt",std::ios::in);
	while(!input.eof()){
		getline(input , line);
		if(line!="\n" && line!=" " && line!=""){
			std::stringstream ss;
			ss<<line;
			temp_id = get_int_number(ss,',');
			temp_name = get_full_name(ss,',');
            temp_accuracy = get_int_number(ss,',');
            temp_investment  = get_double_number(ss,',');
            //Player temp_player(temp_id,temp_name,temp_accuracy,temp_investment);
            players.push_back(new Player(temp_id,temp_name,temp_accuracy,temp_investment));
			}
	}
	input.close();
}
void Game::print_players(){
	std::cout<<"Players:"<<std::endl;
	for(int i = 0; i < players.size(); i++){
		std::cout<<"\tid:"<<players[i]->get_id()<<std::endl;
		std::cout<<"\tname:"<<players[i]->get_name()<<std::endl;
		std::cout<<"\taccuracy:"<<players[i]->get_accuracy()<<std::endl;
		std::cout<<"\tinvestment:"<<players[i]->get_investment()<<std::endl;
		std::cout<<"\tparticipation status: "<<players[i]->is_participate()<<std::endl;
		if(players[i]->is_participate()){
			Position* temp=players[i]->get_player_pos();
			std::cout<<"\t\tlocation :"<<temp->get_row()<<"-"<<temp->get_col()<<"-"<<temp->get_direction()<<std::endl;
			std::cout<<"\t\tsponsor status: "<<players[i]->has_sponsor()<<std::endl;
			if(players[i]->has_sponsor()){
				std::vector <Sponsor*> temp = players[i]->get_sponsors();
				for(int j=0; j < temp.size(); j++){
					std::cout<<"\t\t\tsponsor "<<j+1<<" :"<<temp[j]->get_supporter_id()<<" "<<temp[j]->get_supporter_money()<<std::endl;
				}
			}
			std::cout<<"\t\tweapon status: "<<players[i]->has_weapon()<<std::endl;
			if(players[i]->has_weapon()){
				Weapon* temp = players[i]->get_weapon();
				std::cout<<"\t\t\tweapon :"<<temp->get_model()<<std::endl;
			}
		}
		std::cout<<std::endl;
	}
}
void Game::get_weapons_info(){
	std::ifstream input;
	std::string temp_model,line;
	int temp_power,temp_effective_bord;
	double temp_hiring_price;
	std::stringstream ss;

	input.open("weapons.txt",std::ios::in);
	while(!input.eof()){
		getline(input , line);
		if(line!="\n" && line!=" " && line!=""){
			std::stringstream ss;
			ss<<line;
			temp_model = get_full_name(ss,',');
            temp_power = get_double_number(ss,',');
            temp_effective_bord  = get_double_number(ss,',');
            temp_hiring_price = get_double_number(ss,',');
            weapons.push_back(new Weapon(temp_model,temp_power,temp_effective_bord,temp_hiring_price));
			}
	}
	input.close();
}
void Game::print_weapons(){
	std::cout<<"weapons:"<<std::endl;
	for(int i=0;i<weapons.size();i++){
		std::cout<<"\tmodel:"<<weapons[i]->get_model()<<std::endl;
		std::cout<<"\tpower:"<<weapons[i]->get_power()<<std::endl;
		std::cout<<"\teffective_bord:"<<weapons[i]->get_effective_bord()<<std::endl;
		std::cout<<"\thiring_price:"<<weapons[i]->get_hiring_price()<<std::endl;
		std::cout<<std::endl;
	}
}
int Game::return_index_of_player_by_id(int id){
	for (int i = 0; i < players.size(); i++){
		if(players[i]->get_id()==id)
			return i;
	}
	return (-1);
}
void Game::manage_tournoment(){
	std::string command="",line;
	int game_status=NO_GAME,flag=NORMALL_FINISH;
	while(command != "endtournament"){
		if(flag == NORMALL_FINISH)
			getline(std::cin,line);
		else{
			if(flag == NEWGAME_FINISH)
				line = "newgame";
			else if(flag == ENDTOURNAMENT_FINISH)
				line = "endtournament";
			flag = NORMALL_FINISH;
		}

		std::stringstream ss(line);
		command="";
		ss >> command;
		if(command == "newgame"){
			game_status = INITITAION;
			clean_remained_data();
			initiate_new_game();
			game_status = PREPRATION;
		}
		else if(command == "supports" && game_status == PREPRATION){
			sponsorship(ss);
		}
		else if(command == "purchase" && game_status == PREPRATION){
			weapon_purchase(ss);
		}
		else if(command == "startgame" && game_status == PREPRATION){
			do_final_registration();
			game_status = ACTIVE_GAME;
			flag = start_game();
			if(flag == NORMALL_FINISH){
				report_result();
			}
			game_status = NO_GAME;
		}
	}
}
void Game::initiate_new_game(){
	int num_of_players,id,row,col,index;
	char direction;
	std::cin >> num_of_players;
	std::cin.ignore();
	std::string line;
	round_index.clear();
	for(int i=0; i<num_of_players; i++){
		getline(std::cin, line);
		std::stringstream ss(line);
		ss >> id;
		index = return_index_of_player_by_id(id);
		if(index==-1)
			continue;
		row=get_int_number(ss, ':');
		col=get_int_number(ss, ':');
		ss >> direction;
		round_index.push_back(index);
		players[index]->set_player_pos(row, col, direction);
		players[index]->set_participation(true);
		players[index]->set_health(100);
	}
	int random_seed;
	std::cin>>random_seed;
	srand(random_seed);
	std::cin>>participation_fee>>ticket_revenue;
}
void Game::sponsorship(std::stringstream& ss){
	int sponsor_id;
	ss >> sponsor_id;
	int sponsor_index = return_index_of_player_by_id(sponsor_id);
	if(sponsor_index == -1 || players[sponsor_index]->is_participate())
		return;
	char delemitere;
	ss >> delemitere;
	if(delemitere != '>')
		return;
	int player_id;
	ss >> player_id;
	int player_index = return_index_of_player_by_id(player_id);
	if(player_index == -1 || !players[player_index]->is_participate())
		return;
	std::string extra;
	ss >> extra;
	if (extra != "for")
		return;
	double supporter_money;
	ss >> supporter_money;
	if(supporter_money <= players[sponsor_index]->get_investment()){
		players[player_index]->set_sponsor_status(true);
		players[player_index]->add_sponsor(Sponsor(sponsor_id,supporter_money));
		players[player_index]->add_investment(supporter_money);
		players[sponsor_index]->add_investment(-supporter_money);
	}
}
void Game::weapon_purchase(std::stringstream& ss){
	int player_id;
	ss >> player_id;
	int player_index = return_index_of_player_by_id(player_id);
	if(player_index == -1 || !players[player_index]->is_participate())
		return;
	char delemitere;
	ss >> delemitere;
	if(delemitere != '<')
		return;
	std::string gun_model = get_full_name(ss , ',');
	for(int i=0; i <weapons.size(); i++){
		if(weapons[i]->get_model() == gun_model){
			players[player_index]->set_weapon_status(true);
			players[player_index]->add_weapon(*weapons[i]);
			return;
		}
	}
}
int Game::start_game(){
	std::string command="",line;
	int index=0;
	while(command != "endtournament" && command != "newgame" && !is_game_finished()){
		getline(std::cin,line);
		std::stringstream ss(line);
		command="";
		ss >> command;
		if(command == "surrender"){
			while(!players[round_index[index]]->is_participate())
				increase_index(index,round_index.size());
			players[round_index[index]]->set_participation(false);
		}
		else if(command == "shoot"){
			int counter=0;
			while(!players[round_index[index]]->has_weapon() || !players[round_index[index]]->is_participate()){
				if(counter==round_index.size()){
					break;
				}
				increase_index(index,round_index.size());
				counter++;
			}
			if(counter==round_index.size())
				continue;
			shoot(ss,round_index[index]);
		}
		increase_index(index,round_index.size());
	}
	if(command == "endtournament")
		return ENDTOURNAMENT_FINISH;
	if(command == "newgame")
		return NEWGAME_FINISH;
	return NORMALL_FINISH;
}
void Game::shoot(std::stringstream& ss, int player_index){
	int col,row,dx=0,dy=0;
	row = get_int_number(ss, ':');
	ss >> col;
	char direction = players[player_index]->get_player_pos()->get_direction();
	initialize_delta(dx,dy,direction);
	int origin_col = players[player_index]->get_player_pos()->get_col() + dx;
	int origin_row = players[player_index]->get_player_pos()->get_row() + dy;
	double effectiveness = effectivity(col, row, origin_col, origin_row, players[player_index]->get_weapon()->get_effective_bord());
	int col_error = error_in_shoot(players[player_index]->get_accuracy());
	int row_error = error_in_shoot(players[player_index]->get_accuracy());

	for(int i=0; i<round_index.size(); i++){
		if(!players[i]->is_participate())
			continue;
		int shoot_result = bullet_in_position(players[i]->get_player_pos(),col+col_error,row+row_error);
		if(shoot_result!=0){
			double damage =  shoot_result*effectiveness*players[player_index]->get_weapon()->get_power();
			players[i]->set_health(players[i]->get_health() - damage);
			if(players[i]->get_health() == 0) {// was killed
				players[i]->set_participation(false);
				players[i]->add_num_of_deaths();
				players[player_index]->add_num_of_kills();
			}
			std::string organ;
			switch(shoot_result){
				case HEAD:
					organ = "head";
					break;
				case CHEST:
					organ = "chest";
					break;
				case ABDOMEN:
					organ = "abdomen";
					break;
				case ARMS_OR_FEET:
					organ = "arms or feet";
			}
			std::cout<<"player "<<players[player_index]->get_id()<<" hits player "<<players[i]->get_id()<<" in the "<<organ<<"\n";
			return;
		}
	}
	std::cout<<"player "<<players[player_index]->get_id()<<" missed\n";
}
bool Game::is_game_finished(){
	int counter=0;
	for(int i=0; i<round_index.size(); i++){
		if(players[round_index[i]]->is_participate())
			counter++;
	}
	if(counter <=1 )
		return true;
	return false;
}
void Game::report_result(){
	int index_of_winner;
	for(int i=0; i<round_index.size(); i++){
		if(players[round_index[i]]->is_participate()){
			index_of_winner = round_index[i];
			break;
		}
	}
	players[index_of_winner]->add_investment(ticket_revenue/2);
	std::cout<<"player "<<players[index_of_winner]->get_id()<<" won the game"<<std::endl;
	double sponsors_payback=0;
	if(players[index_of_winner]->has_sponsor()){
		std::vector <Sponsor*> temp = players[index_of_winner]->get_sponsors();
		for(int j=0; j < temp.size(); j++){
			int sponsor_index = return_index_of_player_by_id(temp[j]->get_supporter_id());
			players[sponsor_index]->add_investment(temp[j]->get_supporter_money());
			players[index_of_winner]->add_investment(- temp[j]->get_supporter_money());
			std::cout<<"player "<<players[index_of_winner]->get_id()<<" returns "<<temp[j]->get_supporter_money()
				<<" dollors to sponsor " <<temp[j]->get_supporter_id()<<std::endl;
			sponsors_payback += temp[j]->get_supporter_money();
		}
	}
	std::cout<<"player "<<players[index_of_winner]->get_id()<<" cashed in "
		<<ticket_revenue/2 - sponsors_payback<<" dollars"<<std::endl;
}
void Game::do_final_registration(){
	for(int i=0; i<round_index.size(); i++){
		double player_money = players[round_index[i]]->get_investment();
		if(player_money < participation_fee){
			players[round_index[i]]->set_participation(false);
			continue;
		}
		players[round_index[i]]->add_investment(-participation_fee);
		player_money -= participation_fee;
		if(players[round_index[i]]->has_weapon()){
			double weapon_money = players[round_index[i]]->get_weapon()->get_hiring_price();
			if(player_money < weapon_money){
				players[round_index[i]]->set_weapon_status(false);
				continue;
			}
			players[round_index[i]]->add_investment(-weapon_money);
		}
	}
}
void Game::clean_remained_data(){
	round_index.clear();
	for(int i=0; i<players.size(); i++){
		players[i]->set_participation(false);
		players[i]->set_health(0);
		players[i]->set_weapon_status(false);
		players[i]->set_sponsor_status(false);
		players[i]->add_sponsor(Sponsor(0,0), true);
	}
}
void Game::smart_score_pannel(){
	std::string command,line;
	while(getline(std::cin,line)){
		std::stringstream ss(line);
		command="";
		ss >> command;
		if(command=="show"){
			int num;
			ss >> num;
			std::string extra, option;
			ss >> extra;
			if(extra != "player")
				continue;
			ss >> extra;
			if(extra != "with")
				continue;
			ss >> extra;
			if(extra != "most" && extra != "least")
				continue;
			ss >> option;
			if(option == "capital")
				show_capital(num,extra);
			if(option == "kills")
				show_kills(num,extra);
			if(option == "deaths")
				show_deaths(num,extra);
		}
	}
}
void Game::show_capital(int num, std::string state){
	std::vector <Player*> cp_players = players;
	for(int i=0; i<num; i++){
		int index=0;
		if(state == "most"){
			for(int j=0; j<cp_players.size()-1; j++){
				if(cp_players[j]->get_investment() > cp_players[index]->get_investment())
					index=j;
			}
		}
		if(state == "least"){
			for(int j=0; j<cp_players.size()-1; j++){
				if(cp_players[j]->get_investment() < cp_players[index]->get_investment())
					index=j;
			}
		}
		std::cout<<cp_players[index]->get_name()<<" ("<<cp_players[index]->get_id()
			<<") has "<<cp_players[index]->get_investment()<<" dollars in capital\n";
		cp_players.erase(cp_players.begin() + index);
	}
}
void Game::show_kills(int num, std::string state){
	std::vector <Player*> cp_players = players;
	for(int i=0; i<num; i++){
		int index=0;
		if(state == "most"){
			for(int j=0; j<cp_players.size()-1; j++){
				if(cp_players[j]->get_num_of_kills() > cp_players[index]->get_num_of_kills())
					index=j;
			}
		}
		if(state == "least"){
			for(int j=0; j<cp_players.size()-1; j++){
				if(cp_players[j]->get_num_of_kills() < cp_players[index]->get_num_of_kills())
					index=j;
			}
		}
		std::cout<<cp_players[index]->get_name()<<" ("<<cp_players[index]->get_id()
			<<") has "<<cp_players[index]->get_num_of_kills()<<" kills in total\n";
		cp_players.erase(cp_players.begin() + index);
	}
}
void Game::show_deaths(int num, std::string state){
	std::vector <Player*> cp_players = players;
	for(int i=0; i<num; i++){
		int index=0;
		if(state == "most"){
			for(int j=0; j<cp_players.size()-1; j++){
				if(cp_players[j]->get_num_of_deaths() > cp_players[index]->get_num_of_deaths())
					index=j;
			}
		}
		if(state == "least"){
			for(int j=0; j<cp_players.size()-1; j++){
				if(cp_players[j]->get_num_of_deaths() < cp_players[index]->get_num_of_deaths())
					index=j;
			}
		}
		std::cout<<cp_players[index]->get_name()<<" ("<<cp_players[index]->get_id()
			<<") died "<<cp_players[index]->get_num_of_deaths()<<" times in total\n";
		cp_players.erase(cp_players.begin() + index);
	}
}