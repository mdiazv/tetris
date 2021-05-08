#ifndef DOMAIN_H
#define DOMAIN_H

#include <utility>
#include <vector>
using namespace std;

using Color = int;
using Rotation = int;
using Direction = int;
using Point = pair<int, int>;

const Rotation ROTATE_CW  = 1;
const Rotation NO_ROTATE  = 0;
const Rotation ROTATE_CCW = -1;

const Direction MOVE_LEFT  = -1;
const Direction NO_MOVE    = 0;
const Direction MOVE_RIGHT = 1;

class Block {
    public:
        virtual ~Block() {}
        /** Return current points, accounting for position and rotation */
        vector<Point> points();
        /** Return this blocks color */
        Color color();
        /** Rotate block one step in r direction  */
        void rotate(Rotation r);
        /** Move block by one position in d direction */
        void move(Direction d);
        /** Drop block by one position */
        void drop();
        /** Create a random block positioned at (x,y) */
        static Block* make(int x, int y);
    protected:
        int x, y, r, c;
        vector<vector<Point>> ps;
        Block(int x, int y, int c, vector<vector<Point>> ps)
            : x(x), y(y), r(rand()%ps.size()), c(c), ps(ps) {}
};

class World {
    public:
        World() : current(nullptr) {}
        bool rotate(Rotation r);
        bool move(Direction d);
        bool drop();
        bool spawn();
        vector<vector<int>> render();
    private:
        static const int R = 20, C = 10;
        int Bs[R][C] = {{0}};
        Block *current;
};

#endif
