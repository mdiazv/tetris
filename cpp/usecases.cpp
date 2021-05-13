#include <iostream>
#include <thread>
#include <unistd.h>
#include "usecases.h"

Event InputEventQueue::read() {
    unique_lock<std::mutex> lock(mutex);
    got_events.wait(lock, [this]{ return !events.empty(); });
    Event e = events.front();
    events.pop();
    return e;
}

void InputEventQueue::emit(Event e) {
    unique_lock<std::mutex> lock(mutex);
    events.push(e);
    got_events.notify_one();
}

void Player::start(InputEventQueue *ieq) {
    events = ieq;
    alive = true;
    thread = std::thread(&Player::run, this);
}

void Player::gameover() {
    alive = false;
    thread.join();
}

void Game::start() {
    run();
}

void Game::ticker() {
    do {
        usleep(500000);
        if (!pause)
            events.emit(EV_DROP);
    } while (running);
}

void Game::render() {
    WorldView v = w->render();
    out->render(v);
    p->view(v);
}

int Game::run() {
    running = true;
    score = 0;
    p->start(&events);
    thread ticker(&Game::ticker, this);
    do {
        score += w->check_lines();
        if (!w->spawn()) {
            break;
        }
        render();
        bool landed = false;
        do {
            Event e = events.read();
            if (e == EV_QUIT) {
                goto cleanup;
            }
            if (e == EV_PAUSE) {
                pause = !pause;
                continue;
            }
            bool ok = execute(e);
            landed = (e == EV_DROP || e == EV_HARD_DROP) && !ok;
            render();
        } while (!landed);
    } while (w->landed());
cleanup:
    render();
    out->gameover(score);
    p->gameover();
    running = false;
    ticker.join();
    return score;
}

bool Game::execute(Event e) {
    switch (e) {
    case EV_LEFT:        return w->move(MOVE_LEFT);
    case EV_RIGHT:       return w->move(MOVE_RIGHT);
    case EV_ROTATE:      return w->rotate(ROTATE_CW);
    case EV_DROP:        return w->drop();
    case EV_HARD_DROP:   return w->hard_drop();
    }
    assert(e == EV_NONE);
    return true;
}
