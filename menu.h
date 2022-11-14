/**
 * File              : menu.h
 * Author            : Igor V. Sementsov <ig.kuzm@gmail.com>
 * Date              : 13.11.2022
 * Last Modified Date: 14.11.2022
 * Last Modified By  : Igor V. Sementsov <ig.kuzm@gmail.com>
 */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <string.h>
#include "readdocs/readdocs.h"
#include "strsplit.h"

static void 
open_file(GFile *file, GtkTextBuffer *buffer){
	
	const char *filename = g_file_get_path(file);
	g_print("OPEN FILE: %s\n", filename);

	const char *basename = g_file_get_basename(file);
	char **tokens = NULL;
	int count = strsplit(basename, ".", &tokens);
	if (count > 0){
		char *extension = tokens[count -1];
		if (extension){
			if (strcmp(extension, "doc") == 0 
					|| strcmp(extension, "DOC") == 0
					|| strcmp(extension, "Doc") == 0
			   ){
				const char *text = readdocs_doc(filename);
				g_print("TEXT: %s\n", text);
				gtk_text_buffer_set_text(buffer, text, -1);
			}
			if (strcmp(extension, "docx") == 0 
					|| strcmp(extension, "DOCX") == 0
					|| strcmp(extension, "Docx") == 0
					|| strcmp(extension, "DocX") == 0
			   ){
				const char *text = readdocs_docx(filename);
				gtk_text_buffer_set_text(buffer, text, -1);
			}			
		}
	}
}

static void
on_open_response (GtkDialog *dialog,
                  int        response)
{
	GtkTextBuffer *buffer = gtk_object_get_data(GTK_OBJECT(dialog), "buffer");	
	if (response == GTK_RESPONSE_ACCEPT){
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		GFile *file = gtk_file_chooser_get_file (chooser);
		open_file (file, buffer);
	}
	gtk_widget_destroy (GTK_WIDGET(dialog));
}

void
open_file_dialog (GtkButton *button,
		gpointer   user_data)
{

	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

	dialog = gtk_file_chooser_dialog_new ("Open File",
                                        GTK_WINDOW(user_data),
                                        action,
                                        "Cancel",
                                        GTK_RESPONSE_CANCEL,
                                        "Open",
                                        GTK_RESPONSE_ACCEPT,
                                        NULL);

	gtk_object_set_data(GTK_OBJECT(dialog), "buffer", 
			gtk_object_get_data(GTK_OBJECT(user_data), "buffer"));

	GtkFileFilter *filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(filter, "*.[dD][oO][cC]");
	gtk_file_filter_add_pattern(filter, "*.[dD][oO][cC][xX]");
	gtk_file_chooser_set_filter(GTK_FILE_CHOOSER(dialog), filter);
	gtk_widget_show (dialog);

	g_signal_connect (dialog, "response",
                    G_CALLBACK (on_open_response),
					NULL);	
}

void
save_file_dialog (GtkButton *button,
		gpointer   user_data)
{
	GtkWidget *dialog;
	GtkFileChooser *chooser;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Save File",
										  GTK_WINDOW(user_data),
										  action,
										  "Cancel",
										  GTK_RESPONSE_CANCEL,
										  "Save",
										  GTK_RESPONSE_ACCEPT,
										  NULL);
	chooser = GTK_FILE_CHOOSER (dialog);

	gtk_file_chooser_set_do_overwrite_confirmation (chooser, TRUE);

	gtk_file_chooser_set_current_name (chooser,
										 "Untitled document");

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	  {
		char *filename;

		filename = gtk_file_chooser_get_filename (chooser);
		/*save_to_file (filename);*/
		g_free (filename);
	  }

	gtk_widget_destroy (dialog);
}

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
	g_signal_connect(G_OBJECT(openMi), "activate",
			G_CALLBACK(open_file_dialog), window);	

	GtkWidget *saveMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), saveMi);
	g_signal_connect(G_OBJECT(saveMi), "activate",
			G_CALLBACK(save_file_dialog), window);	
	
	GtkWidget *sep = gtk_separator_menu_item_new();
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), sep);
	
	GtkWidget *quitMi = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, accel_group);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);
	g_signal_connect(G_OBJECT(quitMi), "activate",
			G_CALLBACK(gtk_main_quit), window);  

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
