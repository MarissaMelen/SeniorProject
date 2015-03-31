#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <gtk/gtk.h>
#include "monsterReader.hpp"
#include "monster.hpp"
#include "MonsterFrame.hpp"
#include "ListFrame.hpp"
#include "ButtonsFrame.hpp"

class Window {
private:
	GtkWidget *window;
	GtkWidget *m_grid;
	MonsterFrame *l_frame;
	ListFrame *r_frame;
	ButtonsFrame *b_frame;

public:
	//monster_map typedef'd in ButtonsFrame.hpp
	Window(monster_map *m, std::string *biome_loc, std::vector<monster> *biome);
};

#endif //WINDOW_HPP
