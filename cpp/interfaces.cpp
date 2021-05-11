#include <sstream>
#include <unistd.h>
#include <ncurses.h>
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

CursesOutput::CursesOutput() {
    initscr();
    keypad(stdscr, true);
    halfdelay(10);
    clear();
    noecho();
}

CursesOutput::~CursesOutput() {
    endwin();
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
    }
}

void HumanPlayer::run() {
    while (alive) {
        int ch = getch();
        // Map chars to events and fire
        switch (ch) {
            case KEY_LEFT:  events->emit(EV_LEFT); break;
            case KEY_RIGHT: events->emit(EV_RIGHT); break;
            case KEY_UP:    events->emit(EV_ROTATE); break;
            case KEY_DOWN:  events->emit(EV_DROP); break;
            case ' ':       events->emit(EV_HARD_DROP); break;
        }
    }
}
