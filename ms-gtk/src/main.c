#include <stdlib.h>
#include <time.h>
#include "controller.h"
#include "../../ms/ms.h"

int main(int argc, char** argv) {
    srand(time(0));
    gtk_init(&argc, &argv);
    builder_main = gtk_builder_new();
    builder_game = gtk_builder_new();
    if (!gtk_builder_add_from_resource(builder_main,
                                       "/com/example/ms-gtk/main.ui",
                                       &error)) {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error(&error);
        return 1;
    }
    
    main_win = gtk_builder_get_object(builder_main, "window");
    g_signal_connect(gtk_builder_get_object(builder_main, "easy_start"), "clicked", G_CALLBACK(game_start), mode[0]);
    g_signal_connect(gtk_builder_get_object(builder_main, "normal_start"), "clicked", G_CALLBACK(game_start), mode[1]);
    g_signal_connect(gtk_builder_get_object(builder_main, "hard_start"), "clicked", G_CALLBACK(game_start), mode[2]);
    g_signal_connect(main_win, "destroy", G_CALLBACK (gtk_main_quit), 0);
    gtk_main();
}