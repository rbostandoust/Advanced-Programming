#include "mad_house.h"

MadHouse::MadHouse(){
	yard = new Yard;
}

void MadHouse::add_child(Child* new_child){
	children.push_back(new_child);
}

void MadHouse::get_inputs(){
	int id, radius;
	bool fragile;
	std::string type, fragile_s, line;
	double x1,y1;
	Velocity v;
	Point pos;
	Behaviour behaviour;
	char delimeter;
	std::string word;
	while(getline(std::cin, line)){
		try{
			if(line == "")
				continue;
			delete_space(line);
			std::vector<std::string> result = split_by_camma(line);

			id = atoi(result[0].c_str());
			type = result[1];
			fragile_s = result[2];
			if(fragile_s == "true")
				fragile = 1;
			else if(fragile_s == "false")
				fragile = 0;
			else 
				throw BadInputExeption();
			pos.x = atof(result[3].c_str());
			pos.y = atof(result[4].c_str());
			v.x = atof(result[5].c_str());
			v.y = atof(result[6].c_str());
			radius = atoi(result[7].c_str());
			behaviour.anger = atoi(result[8].c_str());
			behaviour.charisma = atoi(result[9].c_str());
			behaviour.courage = atoi(result[10].c_str());

			Child* new_child = make_right_sub_class(id, radius, fragile, v, pos, behaviour, type);
			add_child(new_child);
		} 
		catch(BadInputExeption ex){
			std::cerr << "Error in line " << id << " of inputs.\n";
		}
	}
}

void MadHouse::simulate(int T, int dt){
	for (int i = 0; i <= T/dt; i++)
	{
		if(i != 0)
			move_children(dt);
		highlight_and_determin_collision_with_wall();
		highlight_collision_with_children();
		determin_result_with_children();
		break_broken_children();
		print_round_status(i);
		delete_dead_children();
	}
}


void MadHouse::print_round_status(int round_num){
	std::cout << "#" << round_num << std::endl;
	for (int i = 0; i < children.size(); ++i)
		children[i]->print_status();
}

void MadHouse::move_children(int dt){
	for (int i = 0; i < children.size(); ++i)
		children[i]->move(dt);
}


void MadHouse::highlight_and_determin_collision_with_wall(){
	for (int i = 0; i < children.size(); i++){
		if(yard->is_in_wall(children[i]->get_pos())){
			children[i]->set_death();
			continue;
		}
		int x_dir = 1, y_dir = 1;
		bool flag = 0;
		for (int teta = 0; teta < 360; teta += STEP)
		{
			Point perimeter;
			perimeter.x = children[i]->get_pos().x + (children[i]->get_radius() * cos (teta * PI / 180));
			perimeter.y = children[i]->get_pos().y + (children[i]->get_radius() * sin (teta * PI / 180));
			if(yard->is_in_wall(perimeter)){
				if(teta == 90 || teta == 270)
					y_dir = -1;
				else if(teta == 0 || teta == 180)
					x_dir = -1;
				else
					flag = 1;
			}
		}
		if(flag == 1 && x_dir == 1 && y_dir == 1)
			x_dir = -1;
		children[i]->refelect_v(x_dir, y_dir);
	}
}

void MadHouse::highlight_collision_with_children(){
	for (int i = 0; i < children.size(); i++)
		for (int j = 0; j < children.size(); j++)
		{
			if(j == i)
				continue;
			if(children[i]->is_nocked_with(children[j]))
				children[i]->deal_with(children[j]);
		}
}

void MadHouse::determin_result_with_children(){
	for (int i = 0; i < children.size(); i++){
		children[i]->effect_changes();
		children[i]->clear_changes();
	}
}

void MadHouse::delete_dead_children(){
	for (int i = 0; i < children.size(); i++){
		if(children[i]->is_dead()){
			delete children[i];
			children.erase(children.begin() + i);
			i--;
		}
	}	
}

void MadHouse::clear_memory(){
	for (int i = 0; i < children.size(); i++)
		delete children[i];	
	children.clear();
	delete yard;
}


void MadHouse::break_broken_children(){
	for (int i = 0; i < children.size(); i++){
		if(children[i]->is_broken()){
			int radius = floor(children[i]->get_radius() / 3);
			double velocity_size = floor( sqrt(pow(children[i]->get_velocity().x, 2) + pow(children[i]->get_velocity().y, 2)) / 6);
			for (int j = 0; j < 6; ++j)
			{
				Velocity v;
				v.x += velocity_size * cos(j * PI / 3);
				v.y += velocity_size * sin(j * PI / 3);
				Point pos = children[i]->get_pos();
				pos.x += children[i]->get_radius() * (2.0/3) * cos(j * PI / 3);
				pos.y += children[i]->get_radius() * (2.0/3) * sin(j * PI / 3);
				Child* new_child = make_right_sub_class(get_last_child_id() + 1, radius, true, v, pos, children[i]->get_behaviour(), children[i]->get_type());
				add_child(new_child);
			}
			children[i]->set_death();
		}
	}
}

int MadHouse::get_last_child_id(){
	return children[children.size() - 1]->get_id();
}




void delete_space(std::string& line){
	for (int i = 0; i < line.length(); ++i)
		if (line[i] == ' '){
			line.erase(line.begin() + i);
			i--;
		}
}

std::vector<std::string> split_by_camma(std::string& line){
	int i = 0;
	std::vector<std::string> result;
	while(result.size() != 10){
		if(line[i] == DELIMETER){
			result.push_back(line.substr(0, i));
			line = line.substr(i + 1);
			i = 0;			
		}
		i++;
	}
	result.push_back(line);
	return result;
}

Child* make_right_sub_class(int _id, int _r, bool _f, Velocity _v, Point _p, Behaviour _b, std::string type){
	if(type == "Peaceful")
		return (new Peaceful(_id, _r, _f, _v, _p, _b));
	else if(type == "Angry")
		return (new Angry(_id, _r, _f, _v, _p, _b));
	else if(type == "Coward")
		return (new Coward(_id, _r, _f, _v, _p, _b));
	else
		throw BadInputExeption();
}