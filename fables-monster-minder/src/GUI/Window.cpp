#include <string>
#include <vector>
#include "Window.hpp"
#include "icon.hpp"

Window::Window(monster_map *m, std::string *biome_loc, std::vector<monster> *biome) {
	//Set up window widget
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 480, 480);
	gtk_container_set_border_width(GTK_CONTAINER(window), 5);
	gtk_window_set_title(GTK_WINDOW(window), "Sylvia's Monster Minder");
	set_window_icon(window);
	gtk_widget_set_hexpand(window, TRUE);
	gtk_widget_set_vexpand(window, TRUE);

	//Set up main grid
	m_grid = gtk_grid_new();
	gtk_widget_set_hexpand(m_grid, TRUE);
	gtk_widget_set_vexpand(m_grid, TRUE);

	//Set up other frames
	l_frame = new MonsterFrame;
	r_frame = new ListFrame(l_frame);
	b_frame = new ButtonsFrame(m, biome_loc, biome, r_frame);

	//Attach frames to the grid
	l_frame->attach_to_grid(m_grid, 0, 0, 1, 1);
	r_frame->attach_to_grid(m_grid, 1, 0, 1, 1);
	b_frame->attach_to_grid(m_grid, 0, 1, 3, 1);

	gtk_container_add(GTK_CONTAINER(window), m_grid);

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);
}

