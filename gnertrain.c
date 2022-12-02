/**
 * File              : gnertrain.c
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 12.11.2022
 * Last Modified Date: 02.12.2022
 * Last Modified By  : Igor V. Sementsov <ig.kuzm@gmail.com>
 */

#include <string.h>
#include <gtk/gtk.h>

#include "menu.h"

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

	GtkWidget *textWindow = gtk_scrolled_window_new(NULL, NULL);
	gtk_paned_add1(GTK_PANED(paned), textWindow);
	gtk_widget_set_size_request(textWindow, 800, 600);

	GtkWidget *textView = gtk_text_view_new();
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(textWindow), textView);
	GtkTextBuffer *buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW(textView));
	gtk_object_set_data(GTK_OBJECT(window), "buffer", buffer);
	g_signal_connect_swapped(G_OBJECT(textView), "populate-popup", 
			G_CALLBACK(show_popup), window);

	GtkWidget *buttonbox = gtk_vbox_new(FALSE, 0);
	gtk_paned_add2(GTK_PANED(paned), buttonbox);

	struct entity **entities = entities_init();
	gtk_object_set_data(GTK_OBJECT(window), "entities", entities);
	for (i=0; entities[i]; ++i){
		GtkWidget *button = gtk_button_new();
		gtk_button_set_label(GTK_BUTTON(button), entities[i]->name);
		if (i > 0){
			GdkColor color;
			//gdk_color_parse (entities[i]->colo, &color);
			gdk_color_parse ("red", &color);
			gtk_widget_modify_bg ( GTK_WIDGET(button), GTK_STATE_NORMAL, &color);
			gtk_text_buffer_create_tag(buffer, 
						entities[i]->colo, "background", entities[i]->colo, NULL); 
			gtk_object_set_data(GTK_OBJECT(button), "colo", entities[i]->colo);
		}
		else 
			gtk_object_set_data(GTK_OBJECT(button), "colo", NULL);
		gtk_box_pack_start(GTK_BOX(buttonbox), button, FALSE, FALSE, 0);
		g_signal_connect(G_OBJECT(button), "clicked", 
				G_CALLBACK(button_clicked), textView);
	}

	gtk_widget_show_all(window);

	gtk_main();
	return 0;
}
