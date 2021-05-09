#ifndef USECASES_H
#define USECASES_H

#include <deque>
#include "domain.h"

using Player = int;
class Output {
    public:
        virtual ~Output() {}
        /** Render game to output */
        virtual void render(World &w) = 0;
        /** Render gameover screen */
        virtual void gameover(int score) = 0;
};

class Input {
    public:
        virtual ~Input() {}
        virtual void view(WorldView);
};

using Event = int;

const Event EV_NONE = 0;
const Event EV_LEFT = 1;
const Event EV_RIGHT = 2;
const Event EV_ROTATE = 3;
const Event EV_DROP = 4;
const Event EV_QUIT = 5;


class InputEventQueue {
    public:
        Event read();
        void emit(Event);
    private:
        deque<Event> events;
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
        /** Game loop */
        void run();
        /** Emits a drop event with a frequency based on current level */
        void ticker();
        /** Apply received event on the world */
        bool execute(Event);
};

#endif
