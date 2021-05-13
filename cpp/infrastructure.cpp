#include "infrastructure.h"
#include <ncurses.h>

WithCurses::WithCurses() {
    initscr();
    keypad(stdscr, true);
    halfdelay(10);
    clear();
    noecho();
}

WithCurses::~WithCurses() {
    endwin();
}
