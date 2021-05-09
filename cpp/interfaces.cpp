#include "interfaces.h"

void StreamOutput::render(World &w) {
    auto v = w.render();
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
