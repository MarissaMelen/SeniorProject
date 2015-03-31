#include "ListFrame.hpp"
#include <functional>
#include <sstream>
#include "turn.hpp"

monsterstate list_dummymon;

void change_active_monster(GtkTreeSelection *selection, gpointer r_f) {
	//Pointer created for convenience
	ListFrame *r_frame = (ListFrame *)r_f;

	GtkTreeIter iter;
	GtkTreeModel *model;
	char *mon_name;

	if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
		//Retreive the monster's name
		gtk_tree_model_get(model, &iter, 0, &mon_name, -1);

		//Set the MonsterFrame's information
		std::string name =  mon_name;
		r_frame->sig_select_monster(name);	
	}
}

ListFrame::ListFrame(MonsterFrame *l_f) {
	//Set up a link to the MonsterManager and a link to the MonsterFrame to be able to retrieve monster information and to be able to edit the MonsterFrame's labels
	l_frame = l_f;

	//Set up the list
	tree_view = gtk_tree_view_new();
	gtk_widget_set_vexpand(tree_view, TRUE);
	gtk_widget_set_hexpand(tree_view, TRUE);
	gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(tree_view), FALSE);

	//Set up the frame	
	r_frame = gtk_frame_new(NULL);
	gtk_frame_set_shadow_type(GTK_FRAME(r_frame), GTK_SHADOW_ETCHED_IN);
	gtk_widget_set_halign(r_frame, GTK_ALIGN_END);
	r_grid = gtk_grid_new();
	gtk_grid_set_row_spacing(GTK_GRID(r_grid), 5);
	gtk_grid_set_column_spacing(GTK_GRID(r_grid), 5);
	gtk_widget_set_vexpand(r_frame, TRUE);
	gtk_widget_set_hexpand(r_frame, TRUE);

	//Attach the tree view to the grid
	gtk_grid_attach(GTK_GRID(r_grid), tree_view, 0, 0, 1, 1);

	//Attach the grid to the frame
	gtk_container_add(GTK_CONTAINER(r_frame), r_grid);

	//Set up the gui list
	cell_renderer = gtk_cell_renderer_text_new();
	gui_list = gtk_tree_view_column_new_with_attributes("List Items", cell_renderer, "text", 0, NULL);	
	gtk_tree_view_column_set_min_width(gui_list, 160);
	gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), gui_list);

	//Generate list of names and indices
	m_data = gtk_list_store_new(1, G_TYPE_STRING);
	gtk_tree_view_set_model(GTK_TREE_VIEW(tree_view), GTK_TREE_MODEL(m_data));
	g_object_unref(m_data);
	list_selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(tree_view));

	//Connect event handlers
	g_signal_connect(list_selection, "changed", G_CALLBACK(change_active_monster), (gpointer)this);
}

void ListFrame::attach_to_grid(GtkWidget *grid, gint left, gint top, gint width, gint height) {
	gtk_grid_attach(GTK_GRID(grid), r_frame, left, top, width, height);
}

void ListFrame::select_monster_by_name(std::string m_name) {
	GtkTreeModel *model;	
	GtkTreeIter iter;

	char *name;
	std::string name_str;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));

	gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
	while (valid) {
		gtk_tree_model_get(model, &iter, 0, &name, -1);
	
		name_str = name;

		//If the data matches, we select the monster
		if (name == m_name) {
			sig_select_monster((*(enemies.begin())).name);
			gtk_tree_selection_select_iter(list_selection, &iter);
			
			return;
		}
	
		//Otherwise keep iterating
		valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(m_data), &iter);
	}
}

void ListFrame::add_monster_to_gui_list(std::string m_name) {
	GtkTreeIter iter;

	const char *name = m_name.c_str();
	gtk_list_store_append(m_data, &iter);
	gtk_list_store_set(m_data, &iter, 0, name, -1);
}

void ListFrame::remove_monster_from_gui_list(std::string m_name) {
	GtkTreeModel *model;	
	GtkTreeIter iter;

	char *name;
	std::string name_str;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));

	gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
	while (valid) {
		gtk_tree_model_get(model, &iter, 0, &name, -1);
	
		name_str = name;

		//If the data matches, we remove the monster
		if (name == m_name) {
			gtk_list_store_remove(m_data, &iter);
			return;
		}
	
		//Otherwise keep iterating
		valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(m_data), &iter);
	}
}

unsigned int ListFrame::get_enemy_count() {
	return enemies.size();
}

void ListFrame::edit_name_in_gui_list(std::string m_name, std::string in_name) {
	GtkTreeModel *model;	
	GtkTreeIter iter;

	char *name;
	std::string name_str;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));

	gboolean valid = gtk_tree_model_get_iter_first(model, &iter);
	while (valid) {
		gtk_tree_model_get(model, &iter, 0, &name, -1);
	
		name_str = name;

		//If the data matches, we change the name of the monster
		if (name == m_name) {
			gtk_list_store_set(m_data, &iter, 0, in_name.c_str(), -1);
			return;
		}
	
		//Otherwise keep iterating
		valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(m_data), &iter);
	}
}

void ListFrame::add_monster_to_list(monsterstate monster){
  std::stringstream ss;
  std::string number; 
  
  while(select_by_name(monster.name).name != "NXMONSTER" || !isdigit(monster.name.back())){
	//Had to implement a stringstream version due to MinGW not supporting to_string
	ss << (enemies.size()+1);
   	ss >> number; 
    monster.name += "-" + number;	
	  //monster.name += "-" + std::to_string(enemies.size()+1);
  }
  enemies.push_back(monster);

  //Add to gui list
  if (select_by_name(monster.name).name != "NXMONSTER")
	  add_monster_to_gui_list(monster.name);
}

void ListFrame::custom_add_monster_to_list(monsterstate monster){
  std::stringstream ss;
  std::string number; 
	
  while(select_by_name(monster.name).name != "NXMONSTER"){
	//Had to implement a stringstream version due to MinGW not supporting to_string
	ss << (enemies.size()+1);
   	ss >> number; 
    monster.name += "-" + number;	
	  //monster.name += "-" + std::to_string(enemies.size()+1);
  }
  enemies.push_back(monster);

	//Add monster to gui_list

  sig_select_monster(monster.name);
  
  //Add to gui list
  if (select_by_name(monster.name).name != "NXMONSTER")
	  add_monster_to_gui_list(monster.name);
}

void ListFrame::remove_monster_from_list(std::string m_name){
  enemies.remove_if([&m_name](monsterstate mon){return mon.name == m_name;});
  
  remove_monster_from_gui_list(m_name); 

  //Shift the selected monster to the first in the list
  select_first_monster();
}

void ListFrame::remove_all_from_list(){
	for (monsterstate monster :  enemies) {
		remove_monster_from_gui_list(monster.name);
	}
	
	enemies.clear();
	
	//Shift the selected monster to the first in the list
	//select_first_monster();
}

void ListFrame::redraw(){
  //gtk_grid_remove_column(r_grid,0);
  for(auto& b:monsterbuttons){
    gtk_widget_destroy(b);
  }
  monsterbuttons.clear();
  int count = 0;
  for(auto& mon:enemies){
    g_print("Adding button for monster %s\n",mon.name.c_str());
    GtkWidget* current_button = gtk_button_new_with_label(mon.name.c_str());
    gtk_grid_attach(GTK_GRID(r_grid), current_button,0,count,1,1);
    g_signal_connect(current_button, "clicked", G_CALLBACK(select_monster), (gpointer) this);
    monsterbuttons.push_back(current_button);
    count++;
  }
  gtk_widget_show_all(r_grid);
}

monsterstate& ListFrame::get_selected_monster(){
  std::string monname = l_frame->get_name();
  return std::ref(select_by_name(monname));
}

monsterstate& ListFrame::select_by_name(std::string name){
  for(auto& mon:enemies){
    g_print("Listframe testing monster %s for %s\n",mon.name.c_str(),name.c_str());
    if(mon.name == name){
      return std::ref(mon);
    }
  }

  return std::ref(list_dummymon);
}

void ListFrame::select_first_monster() {
  if (enemies.size() > 0) {
	  sig_select_monster((*(enemies.begin())).name);

	  //Have the first monster in the gui list selected
	  GtkTreeModel *model;
	  GtkTreeIter iter;
	  model = gtk_tree_view_get_model(GTK_TREE_VIEW(tree_view));
	  gtk_tree_model_get_iter_first(model, &iter);
	  gtk_tree_selection_select_iter(list_selection, &iter);
  }
  else {
	  l_frame->set_monster_to_blank();
  }
}

void ListFrame::sig_select_monster(std::string monster_name){
  g_print("Listframe Signalling monster %s\n",monster_name.c_str());
  monsterstate to_select = select_by_name(monster_name);
  if(to_select.name == "NXMONSTER"){
    l_frame->set_monster_to_blank();
  }else{
    l_frame->set_monster_data(to_select);
  }
}

void ListFrame::damage_monster(std::string m_name, int dmg) {
	monsterstate& monster = select_by_name(m_name);
	monster.curhp -= dmg;
	if(monster.curhp <= 0) {
		remove_monster_from_list(monster.name);
		//redraw();
	}	
	else {
		sig_select_monster(monster.name);
	}
}

void ListFrame::remove_dead_monsters(){
	for (monsterstate mon : enemies) {
		if (mon.curhp <= 0) {
			remove_monster_from_gui_list(mon.name);
		}	
	}
  enemies.remove_if([](monsterstate mon){return mon.curhp <= 0;});
  //Shift the selected monster to the first in the list if there are no more monsters
  if (enemies.size() == 0) {
	  select_first_monster();
  }
}

void ListFrame::advance_turn(){
  passturn(enemies);
  remove_dead_monsters();
  if (enemies.size() > 0) {
	  //Update the monster frame
	  monsterstate& temp = get_selected_monster();
	  sig_select_monster(temp.name);
  }
  else {
	  select_first_monster();
  }
}

void select_monster(GtkButton* button, gpointer data){
  ListFrame* containing = (ListFrame*) data;
  std::string monname = gtk_button_get_label(button);
  g_print("Selecting monster %s\n",monname.c_str());
  containing->sig_select_monster(monname);
}
 
void on_next_turn(GtkButton* button, gpointer data){
    ListFrame* containing = (ListFrame*) data;
    containing->advance_turn();
}
