#include "AttackWindow.hpp"
#include "attackmonster.hpp"
#include "damagemonster.hpp" //customDMG
#include "calcElemDMG.hpp" //checkElem
#include "icon.hpp"
#include <string>
#include <cstdlib>

void on_custom_damage(GtkWidget *dropdown, gpointer w_d) {
	WidgetData *w_data = (WidgetData *)w_d;

	std::string	text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(dropdown));
	if (text == "Custom") {
		if (!gtk_widget_get_visible(w_data->labels[0])) {
			//If the Cust Dmg prompt is invisible, reveal it
			for (int i=0; i<CUST_DMG_LABEL_COUNT; ++i) {
				gtk_widget_set_visible(w_data->labels[i], TRUE);
				gtk_widget_set_visible(w_data->entries[i], TRUE);
			}
		}
	}
	else {
		if (gtk_widget_get_visible(w_data->labels[0])) {
			//If the Cust Dmg prompt is visible, hide it
			for (int i=0; i<CUST_DMG_LABEL_COUNT; ++i) {
				gtk_widget_set_visible(w_data->labels[i], FALSE);
				gtk_widget_set_visible(w_data->entries[i], FALSE);
			}
		}
	}
}

void on_damage_monster(GtkWidget *button, gpointer data) {
	DamageData *d_data = (DamageData *)data;
	//Pointers created for convenience
	AttackWindow *a_window = d_data->a_window;
	GtkWidget *dropdown = d_data->weap_type_dropdown;
	
	//Check to see if we're using custom damage or vanilla damage
	std::string	text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(dropdown));

	if (text == "Custom") {
		a_window->cust_damage_monster();
	}
	else {
		a_window->damage_monster();
	}

	delete a_window;
}

void on_attack_cancel(GtkWidget *button, gpointer data) {
	AttackWindow *a_window = (AttackWindow *)data;
	delete a_window;
}

AttackWindow::AttackWindow(ListFrame *r_f) {
	//Link set up to the ListFrame
	r_frame = r_f;

	//Set up the Attack Window
	a_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(a_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(a_window), 240, 240);
	gtk_container_set_border_width(GTK_CONTAINER(a_window), 10);
	gtk_window_set_title(GTK_WINDOW(a_window), "Attack Monster");
	set_window_icon(a_window);
	a_frame = gtk_frame_new(NULL);
	gtk_frame_set_shadow_type(GTK_FRAME(a_frame), GTK_SHADOW_ETCHED_IN);
	a_grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(a_grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(a_grid), 5);

	//Set up the labels and attach them to the grid
	const char *labels[A_LABEL_COUNT] = {"Weapon Type", "Die Roll", "Base Damage", "Cunning Bonus", "Element1", "Element2"};
	for (int i=0; i<A_LABEL_COUNT; ++i) {
		label = gtk_label_new(labels[i]);
		gtk_grid_attach(GTK_GRID(a_grid), label, 0, i, 1, 1);
	}

	//Set up the entries for the die rolls and base damage
	for (int i=0; i<A_ENTRY_COUNT; ++i) {
		entries[i] = gtk_entry_new();
	}

	//Set up the buttons
	const char *button_labels[A_BUTTON_COUNT] = {"Damage Monster", "Cancel"};
	for (int i=0; i<A_BUTTON_COUNT; ++i) {
		buttons[i] = gtk_button_new_with_label(button_labels[i]);
	}

	const char *weap_names[13] = {"Sword", "Spear", "Axe", "Fist", "Bow", "Crossbow", "Firearm", "Non-mage Tome", "Non-mage Staff", "Knife", "Mage Tome", "Mage Staff", "Custom"};

	//Set up a dropdown menu for weapon types
	weap_list = gtk_combo_box_text_new();
	//Append the options
	for (int i=0; i<13; ++i) {
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(weap_list), weap_names[i]);
	}	
	//Set the default
	gtk_combo_box_set_active(GTK_COMBO_BOX(weap_list), 0);	

	//Set up the cust dmg prompt
	const char *cust_dmg_label_text[A_LABEL_COUNT] = {"Adjusted ARM", "Adjusted DEF", "Adjusted RES", "Damage Multiplier"};
	for (int i=0; i<CUST_DMG_LABEL_COUNT; ++i) {
		cust_dmg_labels[i] = gtk_label_new(cust_dmg_label_text[i]);
		cust_dmg_entries[i] = gtk_entry_new();
	}

	const char *element_names[11] = {"Fire", "Ice", "Nature", "Earth", "Wind", "Spark", "Water", "Light", "Dark", "Null", "None"};

	//Set up a dropdown menu for elements
	//Elem List 1
	elem_list[0] = gtk_combo_box_text_new();
	//Append the options
	for (int i=0; i<11; ++i) {
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(elem_list[0]), element_names[i]);
	}	
	//Set the default
	gtk_combo_box_set_active(GTK_COMBO_BOX(elem_list[0]), 10);	

	//Elem List 2
	elem_list[1] = gtk_combo_box_text_new();
	//Append the options	
	for (int i=0; i<11; ++i) {
		gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(elem_list[1]), element_names[i]);
	}
	//Set the default
	gtk_combo_box_set_active(GTK_COMBO_BOX(elem_list[1]), 10);	

	//Attach buttons and entries to the correct locations on the grid
	//Weapon type dropdown list
	gtk_grid_attach(GTK_GRID(a_grid), weap_list, 1, 0, 1, 1);
	
	//Die Roll Entry
	gtk_grid_attach(GTK_GRID(a_grid), entries[0], 1, 1, 1, 1);

	//Base Damage Entry
	gtk_grid_attach(GTK_GRID(a_grid), entries[1], 1, 2, 1, 1);

	//Cunning Bonus Entry
	gtk_grid_attach(GTK_GRID(a_grid), entries[2], 1, 3, 1, 1);

	//Element 1
	gtk_grid_attach(GTK_GRID(a_grid), elem_list[0], 1, 4, 1, 1);

	//Element 2
	gtk_grid_attach(GTK_GRID(a_grid), elem_list[1], 1, 5, 1, 1);

	//Cust Dmg Prompt
	for (int i=0; i<CUST_DMG_LABEL_COUNT; ++i) {
		gtk_grid_attach(GTK_GRID(a_grid), cust_dmg_labels[i], 0, 6+i, 1, 1);
		gtk_grid_attach(GTK_GRID(a_grid), cust_dmg_entries[i], 1, 6+i, 1, 1);
	}

	//Damage Monster and Cancel buttons
	gtk_grid_attach(GTK_GRID(a_grid), buttons[0], 4, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(a_grid), buttons[1], 4, 1, 1, 1);

	//Generate a WidgetData struct for the event handler
	WidgetData *w_data = new WidgetData;
	for (int i=0; i<CUST_DMG_LABEL_COUNT; ++i) {
		w_data->labels[i] = cust_dmg_labels[i];
		w_data->entries[i] = cust_dmg_entries[i];
	}

	DamageData *d_data = new DamageData;
	d_data->a_window = this;
	d_data->weap_type_dropdown = weap_list;

	//Connect the widgets to their event handlers
	g_signal_connect(weap_list, "changed", G_CALLBACK(on_custom_damage), (gpointer)w_data);
	g_signal_connect(buttons[0], "clicked", G_CALLBACK(on_damage_monster), (gpointer)d_data);
	g_signal_connect(buttons[1], "clicked", G_CALLBACK(on_attack_cancel), (gpointer)this);

	//Display the window
	gtk_container_add(GTK_CONTAINER(a_window), a_grid);
	gtk_widget_show_all(a_window);
	for (int i=0; i<CUST_DMG_LABEL_COUNT; ++i) {
		gtk_widget_hide(cust_dmg_labels[i]);
		gtk_widget_hide(cust_dmg_entries[i]);
	}
}

void AttackWindow::damage_monster() {
	//Access the ListFrame and use damage() to calculate how much hp to remove from the selected monster.
	//If the selected monster's hp is reduced to 0 or below, remove that monster from the list
	
	//Monster created for convenience
	monsterstate& monster = r_frame->get_selected_monster();

	//Dropdown list value retrieval
	//Weapon
	std::string str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(weap_list));
	weapon weapontype = str_to_weap(str);	
	
	//Element 1
	str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(elem_list[0]));
	element atk_elem_1 = read_element(str);

	//Element 2
	str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(elem_list[1]));
	element atk_elem_2 = read_element(str);
		
	int dmg_roll = atoi(gtk_entry_get_text(GTK_ENTRY(entries[0])));
	int base_dmg = atoi(gtk_entry_get_text(GTK_ENTRY(entries[1])));
	int cunningBNS = atoi(gtk_entry_get_text(GTK_ENTRY(entries[2])));
	int monsterARM = (int)monster.basetype.defense;
	int monsterDEF = (int)monster.basetype.armor;
	int monsterRES = (int)monster.basetype.resistance;		
	double elemMOD = checkElem(atk_elem_1, atk_elem_2, monster.basetype);	
	double dmg = damage_target(weapontype, dmg_roll, base_dmg, monsterARM, monsterDEF, monsterRES, elemMOD, cunningBNS);

	r_frame->damage_monster(monster.name, (int)dmg);
}

void AttackWindow::cust_damage_monster() {
	//Access the ListFrame and use damage() to calculate how much hp to remove from the selected monster.
	//If the selected monster's hp is reduced to 0 or below, remove that monster from the list
	
	//Monster created for convenience
	monsterstate monster = r_frame->get_selected_monster();

	//Dropdown list value retrieval
	//Element 1
	std::string str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(elem_list[0]));
	element atk_elem_1 = read_element(str);

	//Element 2
	str = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(elem_list[1]));
	element atk_elem_2 = read_element(str);
		
	int base_dmg = atoi(gtk_entry_get_text(GTK_ENTRY(entries[1])));
	int monsterARM = atoi(gtk_entry_get_text(GTK_ENTRY(cust_dmg_entries[0])));
	int monsterDEF = atoi(gtk_entry_get_text(GTK_ENTRY(cust_dmg_entries[1])));
	int monsterRES = atoi(gtk_entry_get_text(GTK_ENTRY(cust_dmg_entries[2])));
	int dmgMOD = atoi(gtk_entry_get_text(GTK_ENTRY(cust_dmg_entries[3])));
	double elemMOD = checkElem(atk_elem_1, atk_elem_2, monster.basetype);		
	double dmg = customDMG(base_dmg, monsterARM, monsterDEF, monsterRES, elemMOD, dmgMOD);

	r_frame->damage_monster(monster.name, (int)dmg);
}

AttackWindow::~AttackWindow() {
	gtk_widget_destroy(a_window);
}
