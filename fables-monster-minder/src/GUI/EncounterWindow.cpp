#include <cstdlib>
#include "EncounterWindow.hpp"
#include "encounter.hpp"
#include "monsterReader.hpp"
#include "icon.hpp"

void on_choose_biome_loc(GtkWidget *button, gpointer data) {
	GenEncounterData *ge_data = (GenEncounterData *)data;
	EncounterWindow *e_window = ge_data->e_window;

	e_window->request_biome_loc();
}

void on_create_encounter(GtkWidget *button, gpointer data) {
	GenEncounterData *ge_data = (GenEncounterData *)data;
	//Pointers created for convenience 
	std::vector<monsterstate> *monsters = ge_data->monsters;
	std::vector<monster> *biome = ge_data->biome;
	EncounterWindow *e_window = ge_data->e_window;	

	//Clear out the list so that a new encounter can be generated
	e_window->get_list_frame()->remove_all_from_list();

	if (monsterReader(e_window->get_biome_loc(), *biome)) {
		*monsters = makeEncounter(*biome, e_window->get_party_lvl(), e_window->get_party_size(), e_window->get_difficulty());	
		for (unsigned int i=0; i<monsters->size(); ++i) {	
			//Populate the GUI list	
			e_window->get_list_frame()->add_monster_to_list((*monsters)[i]);		
		}

		//Clearing out the vectors here so that the next encounter can be generated
		//I'm assuming that from here on out monsters will be accessed through the ListFrame's monster list. Therefore, the vector of monsterstates is no longer necessary.
		monsters->clear();
		biome->clear();

		//e_window->get_list_frame()->redraw();	
	}
	else {
		//Error handling
		e_window->invalid_biome();	
	}	

	e_window->get_list_frame()->select_first_monster();	
	delete e_window;
}

void on_encounter_cancel(GtkWidget *button, gpointer data) {
	GenEncounterData *ge_data = (GenEncounterData *)data;	
	//Pointers created for convenience	
	EncounterWindow *e_window = ge_data->e_window;

	delete e_window;
}

EncounterWindow::EncounterWindow(GenEncounterData *ge_data, ListFrame *r_f) {
	//Create a link to the List Frame and Biome Location
	r_frame = r_f;
	biome_loc = ge_data->biome_loc;
	
	//Point ge_data to this	
	ge_data->e_window = this;

	//Set up the Generate Encounter Window
	e_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(e_window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(e_window), 480, 240);
	gtk_container_set_border_width(GTK_CONTAINER(e_window), 10);
	gtk_window_set_title(GTK_WINDOW(e_window), "Generate Encounter");
	set_window_icon(e_window);
	e_frame = gtk_frame_new(NULL);
	gtk_frame_set_shadow_type(GTK_FRAME(e_frame), GTK_SHADOW_ETCHED_IN);
	e_grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(e_grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(e_grid), 5);
	
	//Set up the labels and attach them to the grid
	const char *labels[E_LABEL_COUNT] = {"Biome", "Aggregate Party Level", "Party Size", "Difficulty"};	
	for (int i=0; i<E_LABEL_COUNT; ++i) {
		label = gtk_label_new(labels[i]);
		gtk_grid_attach(GTK_GRID(e_grid), label, 0, i, 1, 1);
	}
		
	//Set up a dropdown menu for Difficulty
	diff_list = gtk_combo_box_text_new();
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diff_list), "Easy");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diff_list), "Medium");
	gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(diff_list), "Hard");
	//Set default to Medium
	gtk_combo_box_set_active(GTK_COMBO_BOX(diff_list), 1);

	//Set up the entries for Biome Location, Party Level and Party Size
	for (int i=0; i<E_ENTRY_COUNT; ++i) {
		entries[i] = gtk_entry_new();
	}
	gtk_entry_set_text(GTK_ENTRY(entries[0]), biome_loc->c_str());

	//Set up the buttons
	const char *button_labels[E_BUTTON_COUNT] = {"...", "Generate Encounter", "Cancel"};
	for (int i=0; i<E_BUTTON_COUNT; ++i) {
		buttons[i] = gtk_button_new_with_label(button_labels[i]);
	}

	//Attach buttons and entries to the correct locations on the grid
	//Biome selection entry and button
	gtk_grid_attach(GTK_GRID(e_grid), entries[0], 1, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(e_grid), buttons[0], 2, 0, 1, 1);

	//Total Party Level entry
	gtk_grid_attach(GTK_GRID(e_grid), entries[1], 1, 1, 1, 1);

	//Party size entry
	gtk_grid_attach(GTK_GRID(e_grid), entries[2], 1, 2, 1, 1);

	//Difficulty dropdown menu
	gtk_grid_attach(GTK_GRID(e_grid), diff_list, 1, 3, 1, 1);		

	//Generate Encounter and Cancel buttons
	gtk_grid_attach(GTK_GRID(e_grid), buttons[1], 4, 0, 1, 1);
	gtk_grid_attach(GTK_GRID(e_grid), buttons[2], 4, 1, 1, 1);

	//Connect the buttons to their event handlers
	g_signal_connect(buttons[0], "clicked", G_CALLBACK(on_choose_biome_loc), (gpointer)ge_data);
	g_signal_connect(buttons[1], "clicked", G_CALLBACK(on_create_encounter), (gpointer)ge_data);
	g_signal_connect(buttons[2], "clicked", G_CALLBACK(on_encounter_cancel), (gpointer)ge_data);

	//Display the window
	gtk_container_add(GTK_CONTAINER(e_window), e_grid);
	gtk_widget_show_all(e_window);
}

ListFrame *EncounterWindow::get_list_frame() {
	return r_frame;
}

std::string EncounterWindow::get_biome_loc() {
	*biome_loc = gtk_entry_get_text(GTK_ENTRY(entries[0]));
	return *biome_loc;
}

short EncounterWindow::get_party_lvl() {
	short result = (short)atoi(gtk_entry_get_text(GTK_ENTRY(entries[1])));	
	return result;
}

char EncounterWindow::get_party_size() {
	//gtk_entry_get_text returns a gchar*	
	return ((char)atoi(gtk_entry_get_text(GTK_ENTRY(entries[2]))));
}

difficulty EncounterWindow::get_difficulty() {
	//Check value of combobox
	gchar *text = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(diff_list));
	return str_to_diff(text[0]);
}

void EncounterWindow::request_biome_loc() {
	//Set up the file choosing dialogue
	file_dialog = gtk_file_chooser_dialog_new("Open File", NULL, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
	if (*biome_loc != "") {
		gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_dialog), biome_loc->c_str());
	}

	if (gtk_dialog_run(GTK_DIALOG(file_dialog)) == GTK_RESPONSE_ACCEPT) {
		char *filename;

		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_dialog));
		//Set biome entry	
		gtk_entry_set_text(GTK_ENTRY(entries[0]), filename);
	}	

	gtk_widget_destroy(file_dialog);
}

void EncounterWindow::invalid_biome() {
	//Set up a message dialog
	GtkWidget *popup = gtk_message_dialog_new(GTK_WINDOW(e_window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Invalid Biome File");
	gtk_window_set_title(GTK_WINDOW(popup), "Could not generate encounter");
	gtk_dialog_run(GTK_DIALOG(popup));
	gtk_widget_destroy(popup);
}

EncounterWindow::~EncounterWindow() {
	gtk_widget_destroy(e_window);
}
