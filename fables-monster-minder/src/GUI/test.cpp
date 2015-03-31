#include <gtk/gtk.h>
#include "MonsterFrame.h"
#include "../Monster/monster.hpp";
#include "../Monster/monsterstate.hpp";

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);

	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *grid = gtk_grid_new();
	
	MonsterFrame *test = new MonsterFrame;
	test->attach_to_grid(grid, 0, 0, 1, 1);
	gtk_container_add(GTK_CONTAINER(window), grid);

	gtk_widget_show_all(window);	

	gtk_main();

	return 0;
}
