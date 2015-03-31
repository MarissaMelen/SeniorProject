#pragma once
#include <tuple>
#include <gtk/gtk.h>
void real_apply_status(GtkWidget* button,  std::tuple<monsterstate*,GtkWidget*,GtkWidget*,ListFrame*>* data);
void apply_status_effect(GtkWidget* button, gpointer data);
