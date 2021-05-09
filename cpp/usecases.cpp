#include <unistd.h>
#include "usecases.h"

void Game::start() {
    run();
}

void Game::run() {
    running = true;
    score = 0;
    do {
        score += w->check_lines();
        if (!w->spawn()) {
            break;
        }
        do {
            if (rand() % 10 <= 1) {
                w->move(rand() % 10 < 5 ? MOVE_LEFT : MOVE_RIGHT);
            }
            out->render(*w);
            usleep(5000);
        } while (w->drop());
    } while (w->landed());
    out->render(*w);
    out->gameover(score);
    running = false;
}
