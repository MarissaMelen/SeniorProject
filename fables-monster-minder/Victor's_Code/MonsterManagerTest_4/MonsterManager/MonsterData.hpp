#ifndef MONSTERDATA_HPP
#define MONSTERDATA_HPP

#include <string>
#include <vector>
#include <map>
#include "../Monster/monsterstate.hpp"

struct MonsterData {
	std::map<std::string, std::vector<monsterstate>> monsters;
};

#endif //MONSTERDATA_HPP
