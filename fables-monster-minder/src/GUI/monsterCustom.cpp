#include "ButtonsFrame.hpp"
#include "monsterstate.hpp"
#include "monster.hpp"
#include <gtk/gtk.h>
#include <functional>
#include <string.h>
#include <utility>
#include <cstdlib>
#include "stringDuplication.hpp"
#include "element.hpp"
#include "icon.hpp"

void kill_windows(GtkWidget* button,  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* data){
  //type the data
  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*> info = (std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>) *data;
  //FORMATTING:
  //std::get<0>(info) is the monster being modified
  //std::get<1>(info) is the grid which contains all of the entry fields
  //std::get<2>(info) is the window containing the above (needed here for destruction
  //std::get<3>(info) is the ListFrame, which needs to be signalled after the edit happens
  //cleanup
  gtk_widget_destroy(std::get<2>(info));
}

GtkWidget* make_attribute_box(){
  GtkWidget* box = gtk_combo_box_text_new();
  for(int elem = 0; elem <= (int) specialattribute; elem++){
    std::string representation = write_attribute((enum attribute) elem);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(box),representation.c_str());
  }
  return box;
}

GtkWidget* make_element_box(){
  GtkWidget* box = gtk_combo_box_text_new();
  for(int elem = 0; elem <= (int) noelement; elem++){
    std::string representation = write_element((element) elem);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(box),representation.c_str());
  }
  return box;
}

void alter_monster(GtkWidget* button,  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* data){
  //type the data
  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*> info = (std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>) *data;
  //FORMATTING:
  //std::get<0>(info) is the monster being modified
  //std::get<1>(info) is the grid which contains all of the entry fields
  //std::get<2>(info) is the window containing the above (needed here for destruction
  //std::get<3>(info) is the ListFrame, which needs to be signalled after the edit happens
  //extract everything
  GtkWidget* monster_data[14];
  for (int i=0; i<14; ++i){
    monster_data[i] = gtk_grid_get_child_at(GTK_GRID(std::get<1>(info)),1,i);
  }
  //copy the data out
  char** stats = (char**) malloc(14*sizeof(char*));
  for (int i=0; i<11; ++i){
    stats[i] = cust_strdup(gtk_entry_get_text(GTK_ENTRY(monster_data[i])));
    //stats[i] = strdup(gtk_entry_get_text(GTK_ENTRY(monster_data[i])));
  }
  stats[11] = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(monster_data[11]));
  stats[12] = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(monster_data[12]));
  stats[13] = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(monster_data[13]));
  //set the stats
  std::string input_name = stats[0];
  if(input_name == "NXMONSTER"){
    input_name = "Clever";
  }
  if(input_name != std::get<0>(info)->name){
    //ensure name is unique if it was changed
    while(std::get<3>(info)->select_by_name(input_name).name != "NXMONSTER"){
      input_name += "-c";
    }
	//Update the GUI list name
	std::get<3>(info)->edit_name_in_gui_list(std::get<0>(info)->name, input_name);
  }

  std::get<0>(info)->name = input_name;
  std::get<0>(info)->basetype.movement = atoi(stats[1]);
  std::get<0>(info)->curhp = atoi(stats[2]);
  std::get<0>(info)->basetype.maxhp = atoi(stats[3]);
  std::get<0>(info)->curmp = atoi(stats[4]);
  std::get<0>(info)->basetype.maxmp = atoi(stats[5]);
  std::get<0>(info)->basetype.strength = atoi(stats[6]);
  std::get<0>(info)->basetype.defense = atoi(stats[7]);
  std::get<0>(info)->basetype.armor = atoi(stats[8]);
  std::get<0>(info)->basetype.intelligence = atoi(stats[9]);
  std::get<0>(info)->basetype.resistance = atoi(stats[10]);
  std::get<0>(info)->basetype.elem.first = read_element(stats[11]);
  std::get<0>(info)->basetype.elem.second = read_element(stats[12]);
  std::get<0>(info)->basetype.attr = read_attribute(stats[13]);
  //cleanup
  for (int i=0; i<14; ++i){
    free(stats[i]);
  }
  free(stats);
  gtk_widget_destroy(std::get<2>(info));
  //if the monster is dead due to having 0 hp, it is removed, otherwise update display
  if (std::get<0>(info)->curhp <= 0 || std::get<0>(info)->basetype.maxhp <= 0) {
	  std::get<3>(info)->remove_monster_from_list(std::get<0>(info)->name);
  }
  else {
    std::get<3>(info)->sig_select_monster(std::get<0>(info)->name);
  }
  //std::get<3>(info)->redraw();
  //causes a double free
  //delete data;
}
    

void custom_edit_monster(GtkWidget* button, gpointer data){
  const char *monster_stats[14] = { "Name", "Movement", "Current HP", "Max HP", "Current MP", "Max MP", "STR", "DEF", "ARM", "INT", "RES", "Element 1", "Element 2", "Attribute" };   
  //make the interface
  GtkWidget* encounterwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(encounterwin), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(encounterwin), 10);
  set_window_icon(encounterwin);
  GtkWidget* encountergrid = gtk_grid_new();
  //type the pointer
  ListFrame* provider = (ListFrame*) data;
  //get the monster to edit
  monsterstate* to_alter =  &(provider->get_selected_monster());
  //ui variables
  GtkWidget* labels[14];
  GtkWidget* monster_data[14];
  GtkWidget* label;
  //handle no selection
  if(to_alter->name == "NXMONSTER"){
    label = gtk_label_new("Please select a monster");
    gtk_container_add(GTK_CONTAINER(encounterwin),label);
    gtk_widget_show_all(encounterwin);
    return;
  }
  //generate the ui
  for (int i=0; i<14; ++i) {
    //Attribute Label
    label = gtk_label_new(monster_stats[i]);
    labels[i] = label;
    gtk_grid_attach(GTK_GRID(encountergrid), label, 0, i, 1, 1);

    if(i < 11){
      label = gtk_entry_new();
    }else if(i < 13){
      label = make_element_box();
    }else{
      label = make_attribute_box();
    }
    monster_data[i] = label;
    gtk_grid_attach(GTK_GRID(encountergrid), label, 1, i, 1, 1);
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(monster_data[11]),(int) to_alter->basetype.elem.first);
  gtk_combo_box_set_active(GTK_COMBO_BOX(monster_data[12]),(int) to_alter->basetype.elem.second);
  gtk_combo_box_set_active(GTK_COMBO_BOX(monster_data[13]),(int) to_alter->basetype.attr);

  //Datum is used to store the integer and float data in string format
  char datum[100];

  //Name
  gtk_entry_set_text(GTK_ENTRY(monster_data[0]), 	to_alter->name.c_str());

  //Movement
  sprintf(datum, "%i", (int)to_alter->basetype.movement); //The typecast was required with the current version of to_alter-> I believe movement should be an int though?
  gtk_entry_set_text(GTK_ENTRY(monster_data[1]), datum);

  //Current HP
  sprintf(datum, "%i", (int)to_alter->curhp);
  gtk_entry_set_text(GTK_ENTRY(monster_data[2]), datum);

  //Max HP
  sprintf(datum, "%i", (int)to_alter->basetype.maxhp);
  gtk_entry_set_text(GTK_ENTRY(monster_data[3]), datum);

  //Current MP
  sprintf(datum, "%i", (int)to_alter->curmp);
  gtk_entry_set_text(GTK_ENTRY(monster_data[4]), datum);

  //Max MP
  sprintf(datum, "%i", (int)to_alter->basetype.maxmp);
  gtk_entry_set_text(GTK_ENTRY(monster_data[5]), datum);

  //STR
  sprintf(datum, "%i", (int)to_alter->basetype.strength);
  gtk_entry_set_text(GTK_ENTRY(monster_data[6]), datum);

  //DEF
  sprintf(datum, "%i", (int)to_alter->basetype.defense);
  gtk_entry_set_text(GTK_ENTRY(monster_data[7]), datum);

  //ARM
  sprintf(datum, "%i", (int)to_alter->basetype.armor);
  gtk_entry_set_text(GTK_ENTRY(monster_data[8]), datum);

  //INT
  sprintf(datum, "%i", (int)to_alter->basetype.intelligence);
  gtk_entry_set_text(GTK_ENTRY(monster_data[9]), datum);

  //RES
  sprintf(datum, "%i", (int)to_alter->basetype.resistance);
  gtk_entry_set_text(GTK_ENTRY(monster_data[10]), datum);

  //messy way of passing data
  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* info = new std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>;
  *info = std::make_tuple(to_alter,encountergrid,encounterwin,provider);
  //set up linkage to worker
  GtkWidget* confirmbutton = gtk_button_new_with_label("OK");
  GtkWidget* cancelbutton = gtk_button_new_with_label("Cancel");
  gtk_grid_attach(GTK_GRID(encountergrid),confirmbutton,0,14,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),cancelbutton,1,14,1,1);
  g_signal_connect(confirmbutton, "clicked", G_CALLBACK(alter_monster), info);
  g_signal_connect(cancelbutton, "clicked", G_CALLBACK(kill_windows), info);
  //show
  gtk_container_add(GTK_CONTAINER(encounterwin),encountergrid);
  gtk_widget_show_all(encounterwin);
}


//almost the same as edit_monster()
void create_monster(GtkWidget* button,  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* data){
  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*> info = (std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>) *data;
  GtkWidget* monster_data[14];
  for (int i=0; i<14; ++i){
    monster_data[i] = gtk_grid_get_child_at(GTK_GRID(std::get<1>(info)),1,i);
  }
  char** stats = (char**) malloc(14*sizeof(char*));
  for (int i=0; i<11; ++i){
    stats[i] = cust_strdup(gtk_entry_get_text(GTK_ENTRY(monster_data[i])));
    //stats[i] = strdup(gtk_entry_get_text(GTK_ENTRY(monster_data[i])));
  }
  stats[11] = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(monster_data[11]));
  stats[12] = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(monster_data[12]));
  stats[13] = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(monster_data[13]));

  if(strcmp(stats[0],"NXMONSTER") == 0){
    for (int i=0; i<14; ++i){
      free(stats[i]);
    }
    free(stats);
    gtk_widget_destroy(std::get<2>(info));
    GtkWidget* encounterwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(encounterwin), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(encounterwin), 10);
	set_window_icon(encounterwin);
    GtkWidget* label = gtk_label_new("Please enter a name of the monster");
    gtk_container_add(GTK_CONTAINER(encounterwin),label);
    gtk_widget_show_all(encounterwin);
    return;
  }

  std::get<0>(info)->name = stats[0];
  std::get<0>(info)->basetype.movement = atoi(stats[1]);
  std::get<0>(info)->curhp = atoi(stats[2]);
  std::get<0>(info)->basetype.maxhp = atoi(stats[3]);
  std::get<0>(info)->curmp = atoi(stats[4]);
  std::get<0>(info)->basetype.maxmp = atoi(stats[5]);
  std::get<0>(info)->basetype.strength = atoi(stats[6]);
  std::get<0>(info)->basetype.defense = atoi(stats[7]);
  std::get<0>(info)->basetype.armor = atoi(stats[8]);
  std::get<0>(info)->basetype.intelligence = atoi(stats[9]);
  std::get<0>(info)->basetype.resistance = atoi(stats[10]);
  std::get<0>(info)->basetype.elem.first = read_element(stats[11]);
  std::get<0>(info)->basetype.elem.second = read_element(stats[12]);
  std::get<0>(info)->basetype.attr = read_attribute(stats[13]);
  for (int i=0; i<14; ++i){
    free(stats[i]);
  }
  free(stats);
  gtk_widget_destroy(std::get<2>(info));
  if (std::get<0>(info)->curhp > 0 && std::get<0>(info)->basetype.maxhp > 0) {
    std::get<3>(info)->custom_add_monster_to_list(*std::get<0>(info));
 	if (std::get<3>(info)->get_enemy_count() == 1) {
		std::get<3>(info)->select_first_monster();
	}
    else {
		std::get<3>(info)->sig_select_monster(std::get<0>(info)->name);
		std::get<3>(info)->select_monster_by_name(std::get<0>(info)->name);
	}	
  }
  //std::get<3>(info)->redraw();
  //causes a double free
  //delete data;
}
    
//again, almost identical to custom_edit_monster()
void custom_generate_monster(GtkWidget* button, gpointer data){
  const char *monster_stats[14] = { "Name", "Movement", "Current HP", "Max HP", "Current MP", "Max MP", "STR", "DEF", "ARM", "INT", "RES", "Element 1", "Element 2", "Attribute" };   
  GtkWidget* encounterwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(encounterwin), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(encounterwin), 10);
  set_window_icon(encounterwin);
  GtkWidget* encountergrid = gtk_grid_new();
  ListFrame* provider = (ListFrame*) data;
  monsterstate* to_alter =  new monsterstate;
  GtkWidget* labels[14];
  GtkWidget* monster_data[14];
  GtkWidget* label;
  for (int i=0; i<14; ++i) {
    //Attribute Label
    label = gtk_label_new(monster_stats[i]);
    labels[i] = label;
    gtk_grid_attach(GTK_GRID(encountergrid), label, 0, i, 1, 1);

    if(i < 11){
      label = gtk_entry_new();
    }else if(i < 13){
      label = make_element_box();
    }else{
      label = make_attribute_box();
    }
    monster_data[i] = label;
    gtk_grid_attach(GTK_GRID(encountergrid), label, 1, i, 1, 1);
  }
  gtk_combo_box_set_active(GTK_COMBO_BOX(monster_data[11]),(int) to_alter->basetype.elem.first);
  gtk_combo_box_set_active(GTK_COMBO_BOX(monster_data[12]),(int) to_alter->basetype.elem.second);
  gtk_combo_box_set_active(GTK_COMBO_BOX(monster_data[13]),(int) to_alter->basetype.attr);

  //Datum is used to store the integer and float data in string format
  char datum[100];

  //Name
  gtk_entry_set_text(GTK_ENTRY(monster_data[0]), 	to_alter->name.c_str());

  //Movement
  sprintf(datum, "%i", (int)to_alter->basetype.movement); //The typecast was required with the current version of to_alter-> I believe movement should be an int though?
  gtk_entry_set_text(GTK_ENTRY(monster_data[1]), datum);

  //Current HP
  sprintf(datum, "%i", (int)to_alter->curhp);
  gtk_entry_set_text(GTK_ENTRY(monster_data[2]), datum);

  //Max HP
  sprintf(datum, "%i", (int)to_alter->basetype.maxhp);
  gtk_entry_set_text(GTK_ENTRY(monster_data[3]), datum);

  //Current MP
  sprintf(datum, "%i", (int)to_alter->curmp);
  gtk_entry_set_text(GTK_ENTRY(monster_data[4]), datum);

  //Max MP
  sprintf(datum, "%i", (int)to_alter->basetype.maxmp);
  gtk_entry_set_text(GTK_ENTRY(monster_data[5]), datum);

  //STR
  sprintf(datum, "%i", (int)to_alter->basetype.strength);
  gtk_entry_set_text(GTK_ENTRY(monster_data[6]), datum);

  //DEF
  sprintf(datum, "%i", (int)to_alter->basetype.defense);
  gtk_entry_set_text(GTK_ENTRY(monster_data[7]), datum);

  //ARM
  sprintf(datum, "%i", (int)to_alter->basetype.armor);
  gtk_entry_set_text(GTK_ENTRY(monster_data[8]), datum);

  //INT
  sprintf(datum, "%i", (int)to_alter->basetype.intelligence);
  gtk_entry_set_text(GTK_ENTRY(monster_data[9]), datum);

  //RES
  sprintf(datum, "%i", (int)to_alter->basetype.resistance);
  gtk_entry_set_text(GTK_ENTRY(monster_data[10]), datum);

  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* info = new std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>;
  *info = std::make_tuple(to_alter,encountergrid,encounterwin,provider);
  GtkWidget* confirmbutton = gtk_button_new_with_label("OK");
  GtkWidget* cancelbutton = gtk_button_new_with_label("cancel");
  gtk_grid_attach(GTK_GRID(encountergrid),confirmbutton,0,14,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),cancelbutton,1,14,1,1);
  g_signal_connect(confirmbutton, "clicked", G_CALLBACK(create_monster), info);
  g_signal_connect(cancelbutton, "clicked", G_CALLBACK(kill_windows), info);
  gtk_container_add(GTK_CONTAINER(encounterwin),encountergrid);
  gtk_widget_show_all(encounterwin);
}
