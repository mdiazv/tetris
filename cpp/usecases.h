#ifndef USECASES_H
#define USECASES_H

#include <mutex>
#include <queue>
#include <thread>
#include "domain.h"

class Output {
    public:
        virtual ~Output() {}
        /** Render game to output */
        virtual void render(WorldView v) = 0;
        /** Render gameover screen */
        virtual void gameover(int score) = 0;
};

using Event = int;
const Event EV_NONE      = 0;
const Event EV_LEFT      = 1;
const Event EV_RIGHT     = 2;
const Event EV_ROTATE    = 3;
const Event EV_DROP      = 4;
const Event EV_HARD_DROP = 5;
const Event EV_QUIT      = 6;

class InputEventQueue {
    public:
        /** Read the next event from the queue, whenever we get it */
        Event read();
        void emit(Event);
    private:
        queue<Event> events;
        mutex mutex;
        condition_variable got_events;
};

class Player {
    public:
        virtual ~Player() {}
        /** Let the player know game started */
        void start(InputEventQueue*);
        /** Let the player know game ended */
        void gameover();
        /** Let the player know world state changed */
        virtual void view(WorldView) = 0;
    protected:
        InputEventQueue *events;
        thread thread;
        bool alive = false;
        /** Player game loop */
        virtual void run() = 0;
};

class Game {
    public:
        Game(Player *p, World *w, Output *out) : p(p), w(w), out(out) {}
        /** Start a new game */
        void start();
        /** Query whether game has finished */
        bool finished();
    private:
        Player *p;
        World *w;
        Output *out;
        InputEventQueue events;
        int score = 0;
        int level = 1;
        bool running = false;
        /** Game loop. Returns obtained score */
        int run();
        /** Emits a drop event with a frequency based on current level */
        void ticker();
        /** Apply received event on the world */
        bool execute(Event);
};

#endif
