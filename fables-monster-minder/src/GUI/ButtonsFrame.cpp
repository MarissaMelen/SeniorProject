#include "turn.hpp"
#include "encounter.hpp"
#include "ButtonsFrame.hpp"
#include "monsterCustom.hpp"
#include "statusWindow.hpp"
#include "ListFrame.hpp"
#include <functional>
#include <string.h>

void on_attack_monster(GtkWidget *button, gpointer data) {
	AttackWindowData *a_data = (AttackWindowData *)data;
	//Pointers created for convenience
	AttackWindow *a_window = a_data->a_window;
	ListFrame *r_frame = a_data->r_f;

	//Create the window for attacking monsters
	a_window = new AttackWindow(r_frame);
}

void on_generate_encounter(GtkWidget *button, gpointer data) {
	EncounterWindowData *ew_data = (EncounterWindowData *)data;
	//Pointers created for convenience	
	EncounterWindow *e_window = ew_data->e_window;
	GenEncounterData *ge_data = ew_data->ge_data;
	ListFrame *r_f = ew_data->r_f;

	//Create the window for generating encounters
	e_window = new EncounterWindow(ge_data, r_f);
	
	//Added this in to get rid of the warning that nothing was being done with e_window. Picked get_list_frame because all it does is return a pointer
	e_window->get_list_frame(); 
}

ButtonsFrame::ButtonsFrame(monster_map *m, std::string *biome_loc, std::vector<monster> *biome, ListFrame *r_f) {
	//Set up a link to the monster data for convenience
	monsters = m;
	r_frame = r_f;

	//Create frame and grid
	b_frame = gtk_frame_new(NULL);
	gtk_widget_set_vexpand(b_frame, TRUE);
	gtk_widget_set_hexpand(b_frame, TRUE);
	b_grid = gtk_grid_new();
	

	//Set up buttons	
	const char *button_labels[B_BUTTON_COUNT] = {"Attack Monster", "Next Turn","Generate Encounter","Apply Status","Edit Monster","Create Monster"};
	for (int i=0; i<B_BUTTON_COUNT; ++i) {
		buttons[i] = gtk_button_new_with_label(button_labels[i]);
	//	gtk_grid_attach(GTK_GRID(b_grid), buttons[i], i, 0, 1, 1);
	}	
	//Attaching each button manually for layout control
	gtk_grid_attach(GTK_GRID(b_grid), buttons[0], 0, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(b_grid), buttons[1], 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(b_grid), buttons[2], 2, 0, 1, 1);	
	gtk_grid_attach(GTK_GRID(b_grid), buttons[3], 3, 0, 1, 1);	
	gtk_grid_attach(GTK_GRID(b_grid), buttons[4], 4, 0, 1, 1);	
	gtk_grid_attach(GTK_GRID(b_grid), buttons[5], 5, 0, 1, 1);	

	gtk_container_add(GTK_CONTAINER(b_frame), b_grid);

	AttackWindowData *a_data = new AttackWindowData;
	a_data->a_window = a_window;
	a_data->r_f = r_frame;

	GenEncounterData *ge_data = new GenEncounterData;
	ge_data->monsters = monsters;
	ge_data->biome = biome;
	ge_data->biome_loc = biome_loc;

	EncounterWindowData *ew_data = new EncounterWindowData;
	ew_data->e_window = e_window;
	ew_data->ge_data = ge_data;
	ew_data->r_f = r_frame;

	g_signal_connect(buttons[0], "clicked", G_CALLBACK(on_attack_monster), (gpointer)a_data);
	g_signal_connect(buttons[1], "clicked", G_CALLBACK(on_next_turn), r_frame);
	g_signal_connect(buttons[2], "clicked", G_CALLBACK(on_generate_encounter), (gpointer)ew_data);
	g_signal_connect(buttons[3], "clicked", G_CALLBACK(apply_status_effect), r_frame);
	g_signal_connect(buttons[4], "clicked", G_CALLBACK(custom_edit_monster), r_f);
	g_signal_connect(buttons[5], "clicked", G_CALLBACK(custom_generate_monster), r_f);
}

void ButtonsFrame::attach_to_grid(GtkWidget *grid, gint left, gint top, gint width, gint height) {
	gtk_grid_attach(GTK_GRID(grid), b_frame, left, top, width, height);
}

