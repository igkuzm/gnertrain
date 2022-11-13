/**
 * File              : menu.h
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 13.11.2022
 * Last Modified Date: 13.11.2022
 * Last Modified By  : Igor V. Sementsov <ig.kuzm@gmail.com>
 */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

GtkWidget *
main_menu_bar(GtkWidget * window)
{
	GtkAccelGroup *accel_group = gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

	GtkWidget *menubar = gtk_menu_bar_new();
	
	GtkWidget *fileMi = gtk_menu_item_new_with_label("File");
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);

	GtkWidget *fileMenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
	
	GtkWidget *openMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN, accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openMi);
	
	GtkWidget *sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), sep);
	
	GtkWidget *quitMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
	g_signal_connect(G_OBJECT(quitMi), "activate",
			G_CALLBACK(gtk_main_quit), NULL);  

	GtkWidget *editMi = gtk_menu_item_new_with_label("Edit");
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), editMi);	

	GtkWidget *editMenu = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(editMi), editMenu);	

	GtkWidget *undoMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_UNDO, NULL);
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), undoMi);
	gtk_widget_add_accelerator(undoMi, "activate", accel_group, 
			GDK_z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 	
	
	GtkWidget *redoMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_REDO, accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(editMenu), redoMi);
	gtk_widget_add_accelerator(redoMi, "activate", accel_group, 
			GDK_y, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE); 	

	return menubar;
}

GtkWidget *
main_pmenu(GtkWidget * window)
{
	GtkWidget *hideMi = gtk_menu_item_new_with_label("Minimize");
	gtk_widget_show(hideMi);
	g_signal_connect_swapped(G_OBJECT(hideMi), "activate", 
			G_CALLBACK(gtk_window_iconify), GTK_WINDOW(window));

	return hideMi;
}
