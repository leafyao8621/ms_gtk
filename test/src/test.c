#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../ms/ms.h"

int main(void) {
    // srand(time(0));
    init_game(8, 8, 10);
    // print_board(0);
    print_board(1);
    putchar(10);
    putchar(10);
    check(0, 0);
    print_stat();
    check(2, 7);
    print_stat();
    check(3, 3);
    print_stat();
    check(7, 5);
    print_stat();
    check(7, 0);
    print_stat();
    check(6, 2);
    print_stat();
    check(7, 3);
    print_stat();
    check(5, 2);
    print_stat();
    check(5, 3);
    print_stat();
    check(5, 5);
    print_stat();
    check(5, 6);
    print_stat();
    check(5, 7);
    print_stat();
    check(6, 7);
    print_stat();
    check(1, 4);
    print_stat();
    check(1, 3);
    print_stat();
    check(0, 2);
    print_stat();
    check(0, 3);
    print_stat();
    check(0, 4);
    print_stat();
    check(0, 5);
    print_stat();
    check(0, 7);
    print_stat();
    check(5, 0);
    print_stat();
    check(4, 0);
    print_stat();
    check(4, 1);
    print_stat();
    check(3, 0);
    print_stat();
    check(2, 0);
    print_stat();
    flag(1, 2);
    print_stat();
    flag(1, 2);
    print_stat();
    flag(2, 1);
    print_stat();
    check(3, 1);
    print_stat();
    print_board(0);
    putchar(10);
    end_game();
}