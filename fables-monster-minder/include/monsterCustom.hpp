#include "ButtonsFrame.hpp"
#include <gtk/gtk.h>
#include <functional>
#include <string.h>

void kill_windows(GtkWidget* button,  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* data);
void alter_monster(GtkWidget* button,  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* data);
void custom_edit_monster(GtkWidget* button, gpointer data);
void create_monster(GtkWidget* button,  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* data);
void custom_generate_monster(GtkWidget* button, gpointer data);
