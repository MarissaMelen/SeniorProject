#include "MonsterFrame.hpp"
#include <string.h>
#include "stringDuplication.hpp"

#define NUM_STATS 14

MonsterFrame::MonsterFrame() {
	const char *monster_stats[NUM_STATS] = { "Name", "Movement", "Current HP", "Max HP", "Current MP", "Max MP", "STR", "DEF", "ARM", "INT", "RES", "Element 1", "Element 2", "Attribute" }; 

	//Set up the frame
	l_frame = gtk_frame_new(NULL);
	gtk_frame_set_shadow_type(GTK_FRAME(l_frame), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_vexpand(l_frame, TRUE);
	gtk_widget_set_hexpand(l_frame, TRUE);
	l_grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(l_grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(l_grid), 10);

	//Set up the labels and attach them to the grid
	GtkWidget *label;	
	for (int i=0; i<NUM_STATS; ++i) {
		//Attribute Label
		label = gtk_label_new(monster_stats[i]);
		labels.push_back(label);
		gtk_grid_attach(GTK_GRID(l_grid), label, 0, i, 1, 1);

		//Monster data	
		label = gtk_label_new(" ");
		monster_data.push_back(label);
		gtk_grid_attach(GTK_GRID(l_grid), label, 1, i, 1, 1);
	}

	//Attach the grid to the frame
	gtk_container_add(GTK_CONTAINER(l_frame), l_grid);

}

void MonsterFrame::attach_to_grid(GtkWidget *grid, gint left, gint top, gint width, gint height) {
	gtk_grid_attach(GTK_GRID(grid), l_frame, left, top, width, height);
}

void MonsterFrame::set_monster_data(monsterstate monster) {
	//Datum is used to store the integer and float data in string format
	char datum[100];

	//Name
	gtk_label_set_text(GTK_LABEL(monster_data[0]), 	monster.name.c_str());

	//Movement
	sprintf(datum, "%i", (int)monster.basetype.movement); //The typecast was required with the current version of monster. I believe movement should be an int though?
	gtk_label_set_text(GTK_LABEL(monster_data[1]), datum);

	//Current HP
	sprintf(datum, "%i", (int)monster.curhp);
	gtk_label_set_text(GTK_LABEL(monster_data[2]), datum);

	//Max HP
	sprintf(datum, "%i", (int)monster.basetype.maxhp);
	gtk_label_set_text(GTK_LABEL(monster_data[3]), datum);

	//Current MP
	sprintf(datum, "%i", (int)monster.curmp);
	gtk_label_set_text(GTK_LABEL(monster_data[4]), datum);

	//Max MP
	sprintf(datum, "%i", (int)monster.basetype.maxmp);
	gtk_label_set_text(GTK_LABEL(monster_data[5]), datum);

	//STR
	sprintf(datum, "%i", (int)monster.basetype.strength);
	gtk_label_set_text(GTK_LABEL(monster_data[6]), datum);

	//DEF
	sprintf(datum, "%i", (int)monster.basetype.defense);
	gtk_label_set_text(GTK_LABEL(monster_data[7]), datum);

	//ARM
	sprintf(datum, "%i", (int)monster.basetype.armor);
	gtk_label_set_text(GTK_LABEL(monster_data[8]), datum);

	//INT
	sprintf(datum, "%i", (int)monster.basetype.intelligence);
	gtk_label_set_text(GTK_LABEL(monster_data[9]), datum);

	//RES
	sprintf(datum, "%i", (int)monster.basetype.resistance);
	gtk_label_set_text(GTK_LABEL(monster_data[10]), datum);

	//Element 1
	gtk_label_set_text(GTK_LABEL(monster_data[11]), write_element(monster.basetype.elem.first).c_str());
	//Element 2
	gtk_label_set_text(GTK_LABEL(monster_data[12]), write_element(monster.basetype.elem.second).c_str());
	//Attribute
	gtk_label_set_text(GTK_LABEL(monster_data[13]), write_attribute(monster.basetype.attr).c_str());
}

void MonsterFrame::set_monster_to_blank() {
	for (unsigned int i=0; i<monster_data.size(); ++i) {
		gtk_label_set_text(GTK_LABEL(monster_data[i]), "");
	}
}

char* MonsterFrame::get_name(){
	return cust_strdup(gtk_label_get_text(GTK_LABEL(monster_data[0])));
	//  return strdup(gtk_label_get_text(GTK_LABEL(monster_data[0])));
}
