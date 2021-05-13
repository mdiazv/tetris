#ifndef DOMAIN_H
#define DOMAIN_H

#include <utility>
#include <vector>
using namespace std;

using Color = int;
const Color COLOR_SQUARE  = 1;
const Color COLOR_LINE    = 2;
const Color COLOR_HARRY   = 3;
const Color COLOR_POTTER  = 4;
const Color COLOR_JAY     = 5;
const Color COLOR_KAY     = 6;
const Color COLOR_ROWLING = 7;
const Color COLOR_WALL    = 8;

using Rotation = int;
const Rotation ROTATE_CW  = 1;
const Rotation NO_ROTATE  = 0;
const Rotation ROTATE_CCW = -1;

using Direction = int;
const Direction MOVE_LEFT  = -1;
const Direction NO_MOVE    = 0;
const Direction MOVE_RIGHT = 1;

using Point = pair<int, int>;
using WorldView = vector<vector<int>>;

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
        Color c;
        int x, y, r;
        vector<vector<Point>> ps;
        Block(int x, int y, Color c, vector<vector<Point>> ps)
            : c(c), x(x), y(y), r(rand()%ps.size()), ps(ps) {}
};

class World {
    public:
        World() : current(nullptr) {}
        /** Rotate current block one step in r direction */
        bool rotate(Rotation r);
        /** Move current block by one position in d direction */
        bool move(Direction d);
        /** Drops current block by one position */
        bool drop();
        /** Drops current block all the way to the bottom */
        bool hard_drop();
        /** Spawn a new random block at the top center */
        bool spawn();
        /** Callback to notify that current block has landed */
        bool landed();
        /** Check for lines, delete them, returns number of lines */
        int check_lines();
        /** Return a 2D vector representation of the world */
        WorldView render();
    private:
        static const int R = 20, C = 10;
        int Bs[R][C] = {{0}};
        Block *current;
        /** Is this block in a valid position? */
        bool valid(Block &b);
        /** Clears line y by moving above blocks one line downwards */
        void clear_line(int y);
};

#endif
