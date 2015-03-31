#include "icon.hpp"

void set_window_icon(GtkWidget *window) {	
	//Note: The "images" folder containing the icon should be placed in the same folder as the executable
	gtk_window_set_icon_from_file(GTK_WINDOW(window), "images/Fables of Sylvius.png", NULL);
}
