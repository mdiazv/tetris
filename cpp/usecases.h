#ifndef USECASES_H
#define USECASES_H

#include "domain.h"

using Player = int;
class Output {
    public:
        virtual ~Output() {}
        virtual void render(World &w) = 0;
        virtual void gameover(int score) = 0;
};

class Game {
    public:
        Game(Player *p, World *w, Output *out) : p(p), w(w), out(out) {}
        void start();
        bool finished();
    private:
        Player *p;
        World *w;
        Output *out;
        int score = 0;
        bool running = false;
        void run();
};

#endif
