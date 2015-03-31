#ifndef BUTTONSFRAME_HPP
#define BUTTONSFRAME_HPP

#include <gtk/gtk.h>
#include <vector>
#include <string>
#include <unordered_map>
#include "monsterstate.hpp"
#include "ListFrame.hpp"
#include "EncounterWindow.hpp"
#include "AttackWindow.hpp"

#define B_BUTTON_COUNT 6
typedef std::vector<monsterstate> monster_map;

struct AttackWindowData {
	AttackWindow *a_window;
	ListFrame *r_f;
};

struct EncounterWindowData {
	EncounterWindow *e_window;
	GenEncounterData *ge_data;
	ListFrame *r_f;
};

class ButtonsFrame {
private:
	GtkWidget *b_frame;
	GtkWidget *b_grid;
	GtkWidget *buttons[B_BUTTON_COUNT];
	monster_map *monsters;
	ListFrame *r_frame;
	EncounterWindow *e_window;
	AttackWindow *a_window;

public:
	ButtonsFrame(monster_map *m, std::string *biome_loc, std::vector<monster> *biome, ListFrame *r_f);

	void attach_to_grid(GtkWidget *grid, gint left, gint top, gint width, gint height);

};

#endif //BUTTONSFRAME_HPP
