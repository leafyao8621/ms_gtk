#include "controller.h"
#include "../../ms/ms.h"

GError* error = NULL;
GObject* main_win;
static GObject* game;
int mode[3][4] = {
    {8, 8, 8, 0},
    {16, 16, 40, 1},
    {30, 16, 99, 2}
};
GtkBuilder *builder_main, *builder_game;
static const char* difficulty[] = {
    "/com/example/ms-gtk/easy.ui",
    "/com/example/ms-gtk/normal.ui",
    "/com/example/ms-gtk/hard.ui"
};
struct GridInfo {
    GtkButton* btn;
    int row;
    int col;
} *board, *board_end;
static GtkLabel* indicator;

static inline void update(void) {
    char buf[10];
    unsigned char g;
    for (struct GridInfo* i = board; i != board_end; i++) {
        g = get_grid(i->row, i->col);
        switch (get_stat()) {
        case PENDING:
            if (!(g & CHK_MASK)) {
                if (g & FLG_MASK) {
                    gtk_button_set_label(i->btn, "F");
                } else {
                    gtk_button_set_label(i->btn, "");
                }
                break;
            }
        case WIN:
        case LOSE:
            if (g & MINE_MASK) {
                gtk_button_set_label(i->btn, "*");
            } else {
                snprintf(buf, 10, "%d", g & CNT_MASK);
                gtk_button_set_label(i->btn, buf);
            }
            break;
        }
    }
    switch (get_stat()) {
    case WIN:
        gtk_label_set_label(indicator, "You won!");
        break;
    case LOSE:
        gtk_label_set_label(indicator, "You lost!");
        break;
    }
}

void grid_handle(GtkButton* btn, GdkEvent* event, gpointer data) {
    struct GridInfo g = *(struct GridInfo*)data;
    guint b;
    gdk_event_get_button(event, &b);
    switch (b) {
    case 1:
        check(g.row, g.col);
        break;
    case 3:
        flag(g.row, g.col);
        break;
    }
    update();
}

void game_quit(GObject* obj, gpointer data) {
    gtk_widget_show(GTK_WIDGET(main_win));
    free(board);
    end_game();
}

void game_start(GtkButton* btn, gpointer data) {
    int* pars = (int*)data;
    init_game(pars[0], pars[1], pars[2]);
    gtk_widget_hide(GTK_WIDGET(main_win));
    if (!gtk_builder_add_from_resource(builder_game,
                                       difficulty[pars[3]],
                                       &error)) {
        g_printerr ("Error loading file: %s\n", error->message);
        g_clear_error(&error);
    }
    game = gtk_builder_get_object(builder_game, "window");
    indicator = GTK_LABEL(gtk_builder_get_object(builder_game, "indicator"));
    board = malloc(sizeof(struct GridInfo) * pars[0] * pars[1]);
    board_end = board + pars[0] * pars[1];
    struct GridInfo* b = board;
    char buf[50];
    for (int i = 0; i < pars[1]; i++) {
        for (int j = 0; j < pars[0]; j++, b++) {
            snprintf(buf, 50, "grid%d-%d", i, j);
            b->btn = GTK_BUTTON(gtk_builder_get_object(builder_game, buf));
            b->row = i;
            b->col = j;
            g_signal_connect(b->btn, "button-press-event", G_CALLBACK(grid_handle), b);
        }
    }
    g_signal_connect(game, "destroy", G_CALLBACK(game_quit), 0);
}