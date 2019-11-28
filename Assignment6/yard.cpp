#include "yard.h"

Yard::Yard(){
	declare_map();
	//print_map();
}

void Yard::declare_map(){
	std::ifstream in;
	in.open("map.dat", std::ios::in);
	int n;
	in >> n;
	std::string line;
	for (int i = 0; i < n; i++)
	{
		in >> line;
		map.push_back(line);
	}
}

void Yard::print_map(){
	for (int i = 0; i < map.size(); i++)
		std::cout << map[i] << std::endl;
}

bool Yard::is_in_wall(Point pos){
	if(pos.x < 0 || pos.x >= map.size() || pos.y < 0 || pos.y >= map.size())
		return true;
	if(map[map.size()-floor(pos.y)-1][floor(pos.x)] == BLOCK)
		return true;
	return false;
}