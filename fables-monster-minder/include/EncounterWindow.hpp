#ifndef ENCOUNTERWINDOW_H
#define ENCOUNTERWINDOW_H

#include <vector>
#include <string>
#include "monsterstate.hpp"
#include "encounter.hpp"
#include "ListFrame.hpp"

#define E_LABEL_COUNT 4 //0:biome 1:party level 2:party size 3:difficulty
#define E_ENTRY_COUNT 3 //0: biome 1:party level 2:party size
#define E_BUTTON_COUNT 3 //0:biome 1:create encounter 2:cancel

class EncounterWindow;

struct GenEncounterData {
	std::vector<monsterstate> *monsters;	
	std::vector<monster> *biome;
	std::string *biome_loc;
	EncounterWindow *e_window;
};

class EncounterWindow {
private:
	GtkWidget *e_window;
	GtkWidget *e_frame;
	GtkWidget *e_grid;
	GtkWidget *file_dialog;
	GtkWidget *diff_list;
	GtkWidget *label;
	GtkWidget *entries[E_ENTRY_COUNT];
	GtkWidget *buttons[E_BUTTON_COUNT];
	ListFrame *r_frame;
	std::vector<monster> *biome;
	std::string *biome_loc;

public:
	EncounterWindow(GenEncounterData *ge_data, ListFrame *r_f);

	ListFrame *get_list_frame();
	std::string get_biome_loc();
	short get_party_lvl();
	char get_party_size();
	difficulty get_difficulty();
	void request_biome_loc();
	void invalid_biome();

	~EncounterWindow();
};

#endif //ENCOUNTERWINDOW_H
