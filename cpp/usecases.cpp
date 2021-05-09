#include <iostream>
#include <thread>
#include <unistd.h>
#include "usecases.h"

Event InputEventQueue::read() {
    while (events.empty()) {
        usleep(100);
    }
    Event e = events.front();
    events.pop_front();
    return e;
}

void InputEventQueue::emit(Event e) {
    events.push_back(e);
}

void Game::start() {
    run();
}

void Game::ticker() {
    do {
        if (rand() % 10 <= 1) {
            events.emit(rand() % 10 < 5 ? EV_LEFT : EV_RIGHT);
        }
        usleep(5000);
        events.emit(EV_DROP);
    } while (running);
}

void Game::run() {
    running = true;
    score = 0;
    thread ticker(&Game::ticker, this);
    do {
        score += w->check_lines();
        if (!w->spawn()) {
            break;
        }
        bool landed = false;
        do {
            Event e = events.read();
            if (e == EV_QUIT) {
                goto cleanup;
            }
            bool ok = execute(e);
            landed = e == EV_DROP && !ok;
            out->render(*w);
        } while (!landed);
    } while (w->landed());
cleanup:
    out->render(*w);
    out->gameover(score);
    running = false;
    ticker.join();
}

bool Game::execute(Event e) {
    switch (e) {
    case EV_LEFT:   return w->move(MOVE_LEFT);
    case EV_RIGHT:  return w->move(MOVE_RIGHT);
    case EV_ROTATE: return w->rotate(ROTATE_CW);
    case EV_DROP:   return w->drop();
    }
    assert(e == EV_NONE);
    return true;
}
