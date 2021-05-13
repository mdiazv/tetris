#include <sstream>
#include <unistd.h>
#include <ncurses.h>
#include "domain.h"
#include "interfaces.h"

void StreamOutput::render(WorldView v) {
    for (auto row : v) {
        *out << " | ";
        for (auto c : row) {
            if (c) {
                *out << c << " ";
            } else {
                *out << "  ";
            }
        }
        *out << "|\n";
    }
    *out << " | ";
    for (int i = 0; i < v[0].size(); ++i) {
        *out << "- ";
    }
    *out << "|\n";
}

int rc = 0;

void CursesOutput::render(WorldView v) {
    ostringstream ss;
    StreamOutput so(&ss);
    so.render(v);
    string str = ss.str();
    mvaddstr(1, 0, str.c_str());
    refresh();
}

void CursesOutput::gameover(int score) {
    int R, C;
    getmaxyx(stdscr, R, C);
    mvprintw(R-1, 10, "Game over! [%d points]", score);
    refresh();
}

CursesColorOutput::CursesColorOutput() {
    start_color();
    init_pair(COLOR_SQUARE, COLOR_BLUE, COLOR_BLUE);
    init_pair(COLOR_LINE,   COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(COLOR_HARRY,  COLOR_YELLOW, COLOR_YELLOW);
    init_pair(COLOR_POTTER, COLOR_GREEN, COLOR_GREEN);
    init_pair(COLOR_JAY, COLOR_RED, COLOR_RED);
    init_pair(COLOR_KAY, COLOR_CYAN, COLOR_CYAN);
    init_pair(COLOR_ROWLING, COLOR_WHITE, COLOR_WHITE);
    init_pair(COLOR_WALL, COLOR_BLACK, COLOR_WHITE);
}

void CursesColorOutput::render(WorldView v) {
    int R, C;
    clear();
    getmaxyx(stdscr, R, C);
    int y = R - v.size() - 2;
    int x = C / 2 - v[0].size() - 2;
    for (auto row : v) {
        move(y++, x);
        attron(COLOR_PAIR(COLOR_WALL));
        addstr("  ");
        attroff(COLOR_PAIR(COLOR_WALL));
        for (int c : row) {
            attron(COLOR_PAIR(c));
            addstr("  ");
            attroff(COLOR_PAIR(c));
        }
        attron(COLOR_PAIR(COLOR_WALL));
        addstr("  ");
        attroff(COLOR_PAIR(COLOR_WALL));
        addch('\n');
    }
    move(y++, x);
    attron(COLOR_PAIR(COLOR_WALL));
    addstr("  ");
    for (int i = 0; i < v[0].size(); ++i) {
        addstr("  ");
    }
    addstr("  ");
    attroff(COLOR_PAIR(COLOR_WALL));
    refresh();
}

void CursesColorOutput::gameover(int score) {
    int R, C;
    getmaxyx(stdscr, R, C);
    mvprintw(R-1, 10, "Game over! [%d points]", score);
    refresh();
}


void StreamOutput::gameover(int score) {
    *out << "Game over! [" << score << " points]\n";
}

void RandomPlayer::run() {
    while (alive) {
        if (rand() % 10 <= 1) {
            events->emit(rand() % 10 < 5 ? EV_LEFT : EV_RIGHT);
            usleep(10000);
        }
        if (rand() % 20 <= 0) {
            events->emit(EV_ROTATE);
        }
    }
}

void HumanPlayer::run() {
    while (alive) {
        int ch = getch();
        // Map chars to events and fire
        switch (ch) {
            case KEY_LEFT:  events->emit(EV_LEFT);      break;
            case KEY_RIGHT: events->emit(EV_RIGHT);     break;
            case KEY_UP:    events->emit(EV_ROTATE);    break;
            case KEY_DOWN:  events->emit(EV_DROP);      break;
            case ' ':       events->emit(EV_HARD_DROP); break;
            case 'p':       events->emit(EV_PAUSE);     break;
            case 'q':       events->emit(EV_QUIT);      break;
        }
    }
}
