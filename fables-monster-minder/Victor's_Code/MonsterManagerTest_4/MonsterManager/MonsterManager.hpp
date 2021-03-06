#ifndef MONSTERMANAGER_HPP
#define MONSTERMANAGER_HPP

#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "../Monster/monster.hpp"
#include "../Monster/monsterstate.hpp"

class Window; //Forward declaration to allow Window to reference MonsterManager's functions

class MonsterManager {
private:
	Window *window;
	std::string biome_filename;
	std::vector<monster> biome;
	std::map<std::string, std::vector<monsterstate>> monsters;

public:
	MonsterManager();

	void set_biome_filename(const std::string &fn);
	void load_monsters();

	monsterstate get_monster_data(std::string monster_type, unsigned int index);
};

#endif //MONSTERMANAGER_HPP
