#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_
#include <gtk/gtk.h>

extern GError* error;
extern GObject *main_win;
extern GtkBuilder *builder_main, *builder_game;
extern int mode[3][4];
void game_quit(GObject* obj, gpointer data);
void game_start(GtkButton* btn, gpointer data);
#endif