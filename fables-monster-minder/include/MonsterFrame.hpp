#ifndef MONSTERFRAME_HPP
#define MONSTERFRAME_HPP

#include <gtk/gtk.h>
#include <vector>
#include "monsterstate.hpp"

class MonsterFrame {
private:
	GtkWidget *l_frame;
	GtkWidget *l_grid;
	//MonsterTabs *notebook;
	std::vector<GtkWidget *> labels;
	std::vector<GtkWidget *> monster_data;

public:
	MonsterFrame();

	void attach_to_grid(GtkWidget *grid, gint left, gint top, gint width, gint height);

	void set_monster_data(monsterstate monster);
	void set_monster_to_blank();
  char* get_name();
};

#endif //MONSTERFRAME_HPP
