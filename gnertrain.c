/**
 * File              : gnertrain.c
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 12.11.2022
 * Last Modified Date: 14.11.2022
 * Last Modified By  : Igor V. Sementsov <ig.kuzm@gmail.com>
 */

#include <string.h>
#include <gtk/gtk.h>

#include "menu.h"

const char text[] = " GTK+ is a library for creating graphical user interfaces.\n It works on many UNIX-like platforms, Windows, and on framebuffer devices. GTK+ is released under the GNU Library General Public License (GNU LGPL), which allows for flexible licensing of client applications. GTK+ has a C-based object-oriented architecture that allows for maximum flexibility. Bindings for other languages have been written, including C++, Objective-C, Guile/Scheme, Perl, Python, TOM, Ada95, Free Pascal, and Eiffel. ";

void show_popup(GtkTextView *entry, GtkMenu *menu, gpointer user_data) {
	GtkWidget *hideMi = main_pmenu(user_data);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu), hideMi);
}

void
button_clicked (GtkButton *button,
		gpointer   user_data){

	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(user_data));
	const gchar *colo = gtk_object_get_data(GTK_OBJECT(button), "colo"); 
	
	GtkTextIter start, end;
	gtk_text_buffer_get_selection_bounds(buffer, &start, &end);
	if (colo){
		gtk_text_buffer_apply_tag_by_name(buffer, colo, &start, &end);	
	} else {
		gtk_text_buffer_remove_all_tags(buffer, &start, &end);
	}
}

int main(int argc, char *argv[]) {
	int i;
	
	gtk_init(&argc, &argv);
	
	GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	//gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
	gtk_window_set_title(GTK_WINDOW(window), "GNerTrain");
	
	GtkWidget *pmenu = main_pmenu(window); 
	g_signal_connect(G_OBJECT(window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);

	GtkWidget *box = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), box);

	GtkWidget *menubar = main_menu_bar(window);
	gtk_box_pack_start(GTK_BOX(box), menubar, FALSE, FALSE, 0);

	GtkWidget *paned = gtk_hpaned_new();
	gtk_container_add(GTK_CONTAINER(box), paned);

	GtkWidget *textView = gtk_text_view_new();
	gtk_widget_set_size_request(textView, 800, 600);
	gtk_paned_add1(GTK_PANED(paned), textView);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textView));
	gtk_object_set_data(GTK_OBJECT(window), "buffer", buffer);
	gtk_text_buffer_set_text(GTK_TEXT_BUFFER(buffer), text, -1);
	g_signal_connect_swapped(G_OBJECT(textView), "populate-popup", 
			G_CALLBACK(show_popup), window);

	GtkWidget *buttonbox = gtk_vbox_new(FALSE, 0);
	gtk_paned_add2(GTK_PANED(paned), buttonbox);

	char *ents[] = {"NO", "PERS", "DIAG", "MKB", NULL};
	char *colo[] = {NULL, "red", "green", "blue", NULL};

	gtk_text_buffer_create_tag(buffer, "default_bg", "background", "white", NULL); 
	for (i=0; ents[i]; ++i){
		GtkWidget *button = gtk_button_new();
		gtk_button_set_label(GTK_BUTTON(button), ents[i]);
		if (colo[i]){
			GdkColor color;
			gdk_color_parse (colo[i], &color);
			gtk_widget_modify_bg ( GTK_WIDGET(button), GTK_STATE_NORMAL, &color);
			gtk_text_buffer_create_tag(buffer, colo[i], "background", colo[i], NULL); 
		}
		gtk_object_set_data(GTK_OBJECT(button), "colo", colo[i]);
		gtk_object_set_data(GTK_OBJECT(button), "ent", ents[i]);
		gtk_box_pack_start(GTK_BOX(buttonbox), button, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(button), "clicked", 
				G_CALLBACK(button_clicked), textView);
	}

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
