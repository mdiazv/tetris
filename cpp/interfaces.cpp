#include <unistd.h>
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
