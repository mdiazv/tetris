#ifndef INTERFACES_H
#define INTERFACES_H

#include <iostream>
#include "domain.h"
#include "usecases.h"

class StreamOutput : public Output {
    public:
        StreamOutput(ostream *out) : out(out) {}
        virtual void render(WorldView v);
        virtual void gameover(int score);
    private:
        ostream *out;
};

class CursesOutput : public Output {
    public:
        CursesOutput();
        ~CursesOutput();
        virtual void render(WorldView v);
        virtual void gameover(int score);
};

class RandomPlayer : public Player {
    public:
        virtual void view(WorldView) {}
    private:
        virtual void run();
};

class HumanPlayer : public Player {
    public:
        virtual void view(WorldView) {}
    private:
        virtual void run();
};

#endif
