#ifndef INTERFACES_H
#define INTERFACES_H

#include <iostream>
#include "domain.h"
#include "usecases.h"

class StreamOutput : public Output {
    public:
        StreamOutput(ostream *out) : out(out) {}
        virtual void render(World &w);
        virtual void gameover(int score);
    private:
        ostream *out;
};

#endif
