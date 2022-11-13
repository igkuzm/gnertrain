/**
 * File              : gnertrain.c
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 12.11.2022
 * Last Modified Date: 13.11.2022
 * Last Modified By  : Igor V. Sementsov <ig.kuzm@gmail.com>
 */

#include <string.h>
#include <gtk/gtk.h>

#include "menu.h"

const char text[] = " GTK+ is a library for creating graphical user interfaces. It works on many UNIX-like platforms, Windows, and on framebuffer devices. GTK+ is released under the GNU Library General Public License (GNU LGPL), which allows for flexible licensing of client applications. GTK+ has a C-based object-oriented architecture that allows for maximum flexibility. Bindings for other languages have been written, including C++, Objective-C, Guile/Scheme, Perl, Python, TOM, Ada95, Free Pascal, and Eiffel. ";

void show_popup(GtkTextView *entry, GtkMenu *menu, gpointer user_data) {
	GtkWidget *hideMi = main_pmenu(user_data);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), hideMi);
}

int main(int argc, char *argv[]) {
	gtk_init(&argc, &argv);
	
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GtkWidget *pmenu = main_pmenu(window); 
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *box = gtk_vbox_new(FALSE, 1);
	gtk_container_add(GTK_CONTAINER(window), box);

	GtkWidget *menuBar = main_menu_bar(window);
	gtk_container_add(GTK_CONTAINER(box), menuBar);

	GtkWidget *paned = gtk_vpaned_new();
	gtk_container_add(GTK_CONTAINER(box), paned);

	GtkWidget *textView = gtk_text_view_new();
	gtk_paned_add1(GTK_PANED(paned), textView);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textView));
	//gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), text, -1);
	g_signal_connect_swapped(G_OBJECT(textView), "populate-popup", 
			G_CALLBACK(show_popup), window);

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
