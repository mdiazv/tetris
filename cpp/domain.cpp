#include <iostream>
#include <random>
#include "domain.h"

vector<Point> Block::points() {
    vector<Point> p(4);
    for (int i = 0; i < 4; ++i) {
        p[i] = {ps[r][i].first + x, ps[r][i].second + y};
    }
    return p;
}

Color Block::color() {
    return c;
}

void Block::rotate(Rotation r) {
    this->r = (this->r + r + ps.size()) % ps.size();
}

void Block::move(Direction d) {
    x += d;
}

void Block::drop() {
    y += 1;
}

class Square: public Block {
    public:
        Square(int x, int y) : Block(x, y, 1, {
            {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        }) {}
};

class Line: public Block {
    public:
        Line(int x, int y) : Block (x, y, 2, {
            {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
            {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
        }) {}
};

Block* Block::make(int x, int y) {
    vector<Block> bs = {Square(x, y), Line(x, y)};
    return new Block(bs[rand() % bs.size()]);
}

bool World::rotate(Rotation r) {
    current->rotate(r);
    return true;
}
bool World::move(Direction d) {
    current->move(d);
    return true;
}
bool World::drop() {
    current->drop();
    return true;
}
bool World::spawn() {
    current = Block::make((C-1)/2, 0);
    return true;
}

vector<vector<int>> World::render() {
    vector<vector<int>> w(R, vector<int>(C));
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            w[i][j] = Bs[i][j];
        }
    }
    if (current) {
        Color c = current->color();
        for (auto p : current->points()) {
            w[p.second][p.first] = c;
        }
    }
    return w;
}
