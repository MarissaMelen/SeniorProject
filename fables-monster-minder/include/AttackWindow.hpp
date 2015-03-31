#ifndef ATTACKWINDOW_H
#define ATTACKWINDOW_H

#include <gtk/gtk.h>
#include "ListFrame.hpp"

#define A_ENTRY_COUNT 3 //0:die roll 1:base damage 2:cunning
#define A_LABEL_COUNT 6 //0:weapon type 1:die roll 2:base damage 3:cunning 4:element1 5:element2
#define A_BUTTON_COUNT 2 //0:damage monster 1:cancel
#define CUST_DMG_LABEL_COUNT 4 //0:Adjusted Armor 1:Adjusted Defense
#define CUST_DMG_ENTRY_COUNT 4 //2:Adjusted Resistance 3:Damage Mod

class AttackWindow;

struct WidgetData {
	GtkWidget *labels[CUST_DMG_LABEL_COUNT];
	GtkWidget *entries[CUST_DMG_ENTRY_COUNT];
};

struct DamageData {
	AttackWindow *a_window;
	GtkWidget *weap_type_dropdown;
};

class AttackWindow {
private:
	GtkWidget *a_window;
	GtkWidget *a_frame;
	GtkWidget *a_grid;
	GtkWidget *label;
	GtkWidget *cust_dmg_labels[CUST_DMG_LABEL_COUNT];
	GtkWidget *cust_dmg_entries[CUST_DMG_ENTRY_COUNT];
	GtkWidget *weap_list;
	GtkWidget *elem_list[2];
	GtkWidget *entries[A_ENTRY_COUNT];
	GtkWidget *buttons[A_BUTTON_COUNT];	
	ListFrame *r_frame;

public:
	AttackWindow(ListFrame *r_f);

	void damage_monster();
	void cust_damage_monster();

	~AttackWindow();
};

#endif //ATTACKWINDOW_H
