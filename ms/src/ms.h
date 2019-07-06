#ifndef _MS_H_
#define _MS_H_

#define CHK_MASK  (0x80)
#define FLG_MASK  (0x40)
#define MINE_MASK (0x20)
#define CNT_MASK  (0xf)

typedef unsigned char Grid;

enum Stat {
    LOSE,
    WIN,
    PENDING
};

void print_board(_Bool reveal);
void init_game(int width, int height, int n_mines);
void end_game(void);
void check(int row, int col);
void flag(int row, int col);
enum Stat get_stat(void);
void print_stat(void);
Grid get_grid(int row, int col);
#endif