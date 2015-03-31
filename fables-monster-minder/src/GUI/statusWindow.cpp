#include "monsterCustom.hpp"
#include "statusWindow.hpp"
#include "stringDuplication.hpp"
#include "icon.hpp"
#include <cstdlib>

GtkWidget* make_statustype_box(){
  GtkWidget* box = gtk_combo_box_text_new();
  for(int elem = 0; elem <= (int) specialstatus; elem++){
    std::string representation = write_statustype((statustype) elem);
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(box),representation.c_str());
  }
  return box;
}

void real_apply_status(GtkWidget* button,  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* data){
  //type the data
  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*> info = (std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>) *data;
  //FORMATTING:
  //std::get<0>(info) is the monster being modified
  //std::get<1>(info) is the grid which contains all of the entry fields
  //std::get<2>(info) is the window containing the above (needed here for destruction
  //std::get<3>(info) is the ListFrame, which needs to be signalled after the edit happens
  GtkWidget* typebox = gtk_grid_get_child_at(GTK_GRID(std::get<1>(info)),1,0);
  GtkWidget* durationentry = gtk_grid_get_child_at(GTK_GRID(std::get<1>(info)),1,1);
  GtkWidget* levelentry = gtk_grid_get_child_at(GTK_GRID(std::get<1>(info)),1,2);
  GtkWidget* nameentry = gtk_grid_get_child_at(GTK_GRID(std::get<1>(info)),1,3);
  status toapply;
  std::string type = cust_strdup(gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(typebox)));
  char* duration = cust_strdup(gtk_entry_get_text(GTK_ENTRY(durationentry)));
  char* level = cust_strdup(gtk_entry_get_text(GTK_ENTRY(levelentry)));
  std::string name = cust_strdup(gtk_entry_get_text(GTK_ENTRY(nameentry)));
  toapply.fresh = true;
  toapply.duration = atoi(duration);
  toapply.name = name;
  toapply.level = atoi(level);
  toapply.type = read_statustype(type);
  toapply(std::get<0>(info)->basetype);
  std::get<0>(info)->effects.push_back(toapply);
  if(std::get<0>(info)->basetype.maxhp < std::get<0>(info)->curhp){
    std::get<0>(info)->curhp = std::get<0>(info)->basetype.maxhp;
  }
  if(std::get<0>(info)->basetype.maxmp < std::get<0>(info)->curmp){
    std::get<0>(info)->curmp = std::get<0>(info)->basetype.maxmp;
  }
  gtk_widget_destroy(std::get<2>(info));
  //If the monster would die to the status application, it is removed, otherwise update display 
  if (std::get<0>(info)->curhp <= 0 || std::get<0>(info)->basetype.maxhp <= 0) {
	  std::get<3>(info)->remove_monster_from_list(std::get<0>(info)->name);
  }
  else {
    std::get<3>(info)->sig_select_monster(std::get<0>(info)->name);
  }

  //std::get<3>(info)->redraw();

  return;
}

void apply_status_effect(GtkWidget* button, gpointer data){
  GtkWidget* encounterwin = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(encounterwin), GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(encounterwin), 10);
  set_window_icon(encounterwin);
  GtkWidget* encountergrid = gtk_grid_new();
  //type the pointer
  ListFrame* provider = (ListFrame*) data;
  //get the monster to edit
  monsterstate* to_alter =  &(provider->get_selected_monster());
  //handle no selection
  if(to_alter->name == "NXMONSTER"){
    GtkWidget* label = gtk_label_new("Please select a monster");
    //gtk_grid_attach(GTK_GRID(encountergrid),label,0,0,1,1);
    gtk_container_add(GTK_CONTAINER(encounterwin),label);
    gtk_widget_show_all(encounterwin);
    return;
  }
  GtkWidget* typelabel = gtk_label_new("Type");
  GtkWidget* durationlabel = gtk_label_new("Duration");
  GtkWidget* levellabel = gtk_label_new("Level");
  GtkWidget* namelabel = gtk_label_new("Name");
  GtkWidget* durationentry = gtk_entry_new();
  GtkWidget* levelentry = gtk_entry_new();
  GtkWidget* nameentry = gtk_entry_new();
  GtkWidget* typebox = make_statustype_box();
  gtk_grid_attach(GTK_GRID(encountergrid),typelabel,0,0,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),typebox,1,0,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),durationlabel,0,1,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),durationentry,1,1,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),levellabel,0,2,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),levelentry,1,2,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),namelabel,0,3,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),nameentry,1,3,1,1);
  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* info = new std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>;
  *info = std::make_tuple(to_alter,encountergrid,encounterwin,provider);
  //set up linkage to worker
  GtkWidget* confirmbutton = gtk_button_new_with_label("OK");
  GtkWidget* cancelbutton = gtk_button_new_with_label("Cancel");
  gtk_grid_attach(GTK_GRID(encountergrid),confirmbutton,0,14,1,1);
  gtk_grid_attach(GTK_GRID(encountergrid),cancelbutton,1,14,1,1);
  g_signal_connect(confirmbutton, "clicked", G_CALLBACK(real_apply_status), info);
  g_signal_connect(cancelbutton, "clicked", G_CALLBACK(kill_windows), info);
  //show
  gtk_container_add(GTK_CONTAINER(encounterwin),encountergrid);
  gtk_widget_show_all(encounterwin);
}
  
