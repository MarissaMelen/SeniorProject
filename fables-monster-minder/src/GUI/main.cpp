#include <gtk/gtk.h>
#include "../../include/monsterstate.hpp"
#include "Window.hpp"

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	
	std::vector<monsterstate> monsters;
	std::vector<monster> biome;
	std::string biome_loc;

/*
	std::string test = "Test_1";
	monster montype;
	montype.default_name = "test_name";
	montype.maxhp = 10.0f;
	montype.maxmp = 10.0f;
	montype.strength = 10.0f;
	montype.defense = 10.0f;
	montype.armor = 10.0f;
	montype.intelligence = 10.0f;
	montype.resistance = 10.0f;
	montype.movement = 10.0f;
	montype.attr = noattribute;
	montype.elem.first = noelement;
	montype.elem.second = noelement;

	monsterstate enemy;
	enemy.name = "blank";
	enemy.basetype = montype;
	enemy.curhp = 10;
	enemy.curmp = 10;
	monsters.push_back(enemy);	
*/
	
	Window window(&monsters, &biome_loc, &biome);	
	gtk_main();

	return 0;
}
