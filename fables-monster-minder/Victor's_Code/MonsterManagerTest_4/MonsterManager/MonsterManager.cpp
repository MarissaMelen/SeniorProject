#include "MonsterManager.hpp"
#include "../GUI/Window.hpp"

MonsterManager::MonsterManager() {
	//Initalize the window
	window = new Window(this);
}

void MonsterManager::set_biome_filename(const std::string &fn) {
	biome_filename = fn;
}

istream & operator >> (istream &i, element &e) {
  //Read in element from file
  string input;
  i >> input;

  //Make input lowercase
  for (unsigned int i=0; i<input.size(); ++i)
    {
      input[i] = tolower(input[i]);
    }

  if (input == "fire")
    e = fire;
  else if (input == "ice")
    e = ice;
  else if (input == "nature")
    e = nature;
  else if (input == "earth")
    e = earth;
  else if (input == "wind")
    e = wind;
  else if (input == "spark")
    e = spark;
  else if (input == "water")
    e = water;
  else if (input == "light")
    e = light;
  else if (input == "dark")
    e = dark;
  else if (input == "null")
    e = null;
  else if (input == "none") 
    e = noelement;
  else
    e = specialelement;
  return i;
}

/*
istream & operator >> (istream &i, attribute &a) {
  string input;
  i >> input;
  return i;
}
*/

void MonsterManager::load_monsters() {
	std::ifstream in;
	in.open(biome_filename);

	if (!in.is_open()) {
		//window->error(NO_BIOME_FILE);
		return;
	}
	
	while (!in.eof()) {
		std::string name;
		pair<element, element> elems;
//		attribute attr;
		int move;
		float hp, mp, str, def, arm, intl, res;
		
		in >> name;
		//ignore any lines starting with '#'
		if (name[0] == '#') {
			getline(in, name);
			in >> name;
		}

		//read in values
		in >> move >> hp >> mp >> str >> def >> arm >> intl >> res >> elems.first >> elems.second;// >> attr;

		monster temp;
		temp.name = name;
		temp.maxhp = hp;
		temp.maxhp = mp;
		temp.strength = str;
		temp.defense = def;
		temp.armor = arm;
		temp.intelligence = intl;
		temp.resistance = res;
		temp.movement = move;
		temp.elem.first = elems.first;
		temp.elem.second = elems.second;
//		temp.attr = attr;

		biome.push_back(temp);
	}

	in.close();
}

monsterstate MonsterManager::get_monster_data(std::string monster_type, unsigned int index) {
	if ((monsters.find(monster_type) == monsters.end()) || (index > monsters[monster_type].size())) {
		//Monster is not found
		monster temp_m;
		temp_m.name = "Not found";
		temp_m.movement = 0;
		temp_m.maxhp = 0.0f;
		temp_m.maxmp = 0.0f;
		temp_m.strength = 0.0f;
		temp_m.defense = 0.0f;
		temp_m.armor = 0.0f;
		temp_m.intelligence = 0.0f;
		temp_m.resistance = 0.0f;
		temp_m.elem.first = noelement;
		temp_m.elem.second = noelement;
//		temp_m.attr = dummy;

		monsterstate temp_ms;
		temp_ms.basetype = temp_m;
		temp_ms.name = "Not found";
		temp_ms.curhp = 0;
		temp_ms.curmp = 0;

		return temp_ms;
	}

	return monsters[monster_type][index];
}
