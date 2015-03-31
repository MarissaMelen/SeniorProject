#ifndef LISTFRAME_HPP
#define LISTFRAME_HPP

#include <gtk/gtk.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>
#include "monsterstate.hpp"
#include "MonsterFrame.hpp"

class ListFrame {
private:
	GtkWidget *r_frame;
	GtkWidget *r_grid;
	GtkWidget *tree_view; //GtkTreeView
	GtkCellRenderer *cell_renderer;
	GtkTreeViewColumn *gui_list;
	GtkListStore *m_data;
	GtkTreeSelection *list_selection;
	MonsterFrame *l_frame;	
  std::list<monsterstate> enemies;
  std::vector<GtkWidget*> monsterbuttons;

public:
	//Currently a pointer to the MonsterManager is passed down for convenience. I wonder if there's a better way to do this.
  ListFrame(MonsterFrame *l_f);
  monsterstate& select_by_name(std::string name);
  void attach_to_grid(GtkWidget *grid, gint left, gint top, gint width, gint height);

  //GUI list accessors
  void add_monster_to_gui_list(std::string m_name);
  void remove_monster_from_gui_list(std::string m_name);

  //Monster list accessors
  unsigned int get_enemy_count();
  void edit_name_in_gui_list(std::string m_name, std::string in_name);
  void select_monster_by_name(std::string m_name);
  void add_monster_to_list(monsterstate monster);
  void custom_add_monster_to_list(monsterstate monster);
  void remove_monster_from_list(std::string m_name);
  void remove_dead_monsters();
  void advance_turn();
  void remove_all_from_list();
  void redraw();
  void select_first_monster();
  void sig_select_monster(std::string monster_name);
  monsterstate& get_selected_monster();
  void damage_monster(std::string m_name, int dmg);
};

void select_monster(GtkButton* button, gpointer data);
void on_next_turn(GtkButton* button, gpointer data);
#endif //LISTFRAME_HPP

