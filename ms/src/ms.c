#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ms.h"

static Grid* board = 0;
static int* stack = 0;
static int width = 0;
static int height = 0;
static int n_grids = 0;
static int n_mines = 0;
static int n_mines_rem = 0;
static int n_chk = 0;
static enum Stat stat = PENDING;
static const char* stat_str[] = {
    "Lose",
    "Win",
    "Pending"
};

void print_board(_Bool reveal) {
    Grid* g = board;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++, g++) {
            printf("%c ", (reveal || (*g & CHK_MASK)) ?
                          ((*g & MINE_MASK) ? '*' : ((*g & CNT_MASK) + '0')) :
                          ((*g & FLG_MASK) ? 'f' : '_'));
        }
        putchar(10);
    }
    
}

void init_game(int w, int h, int nm) {
    width = w;
    height = h;
    n_grids = w * h;
    n_mines = nm;
    n_mines_rem = nm;
    n_chk = 0;
    stat = PENDING;
    board = calloc(1, n_grids);
    stack = calloc(sizeof(int), n_grids);
    int temp = 0;
    for (int i = 0; i < n_mines;) {
        temp = rand() % n_grids;
        if (!(board[temp] & MINE_MASK)) {
            board[temp] |= MINE_MASK;
            i++;
        }
    }
    Grid* g = board;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++, g++) {
            if (!(*g & MINE_MASK)) {
                int cnt = 0;
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        if (i + k >= 0 && i + k < height && j + l >= 0 &&
                            j + l < width) {
                            cnt += ((board[(i + k) * width + (j + l)] &
                                   MINE_MASK) >> 5);
                        }
                    }
                }
                *g |= cnt;
            }
        }
    }
}

void end_game(void) {
    free(board);
    free(stack);
}

void flag(int r, int c) {
    Grid* g = board + r * width + c;
    if (!(*g & CHK_MASK)) {
        *g ^= FLG_MASK;
        n_mines_rem += (*g & FLG_MASK) ? -1 : 1;
    }
}

void check(int r, int c) {
    if (!(board[r * width + c] & FLG_MASK) &&
        !(board[r * width + c] & CHK_MASK)) {
        
        if (board[r * width + c] & MINE_MASK) {
            board[r * width + c] |= CHK_MASK;
            stat = LOSE;
            return;
        }
        int* g = stack;
        *(g++) = r * width + c;

        for (; g != stack; ) {
            int temp = *(--g);
            if (!(board[temp] & CHK_MASK)) {
                board[temp] |= CHK_MASK;
                n_chk++;
            }
            int r = temp / width;
            int c = temp % width;
            if (!(board[temp] & CNT_MASK)) {
                for (int k = -1; k < 2; k++) {
                    for (int l = -1; l < 2; l++) {
                        if (r + k >= 0 && r + k < height && c + l >= 0 &&
                            c + l < width) {
                            if (!(board[(r + k) * width + (c + l)] & CHK_MASK)) {
                                *(g++) = (r + k) * width + (c + l);
                                board[(r + k) * width + (c + l)] |= CHK_MASK;
                                n_chk++;
                            }
                        }
                    }
                }
            }
        }
        if (n_chk == (n_grids - n_mines)) stat = WIN;
    }
}

enum Stat get_stat(void) {
    return stat;
}

void print_stat(void) {
    printf("rem %d\n", n_mines_rem);
    puts(stat_str[stat]);
}

Grid get_grid(int row, int col) {
    return board[row * width + col];
}