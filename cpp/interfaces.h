#ifndef INTERFACES_H
#define INTERFACES_H

#include <iostream>
#include "domain.h"

class Output {
    public:
        virtual ~Output() {}
        virtual void render(World &w) = 0;
};

class StreamOutput : public Output {
    public:
        StreamOutput(ostream *out) : out(out) {}
        virtual void render(World &w);
    private:
        ostream *out;
};

#endif
