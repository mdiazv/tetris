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

class Square : public Block {
    public:
        Square(int x, int y) : Block(x, y, COLOR_SQUARE, {
            {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        }) {}
};

class Line : public Block {
    public:
        Line(int x, int y) : Block (x, y, COLOR_LINE, {
            {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
            {{-1, 0}, {0, 0}, {1, 0}, {2, 0}},
        }) {}
};

class Harry : public Block {
    public:
        Harry(int x, int y) : Block (x, y, COLOR_HARRY, {
            {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
            {{1, 0}, {2, 0}, {0, 1}, {1, 1}},
        }) {}
};

class Potter : public Block {
    public:
        Potter(int x, int y) : Block (x, y, COLOR_POTTER, {
            {{1, 0}, {0, 1}, {1, 1}, {0, 2}},
            {{1, 0}, {2, 1}, {0, 0}, {1, 1}},
        }) {}
};

class Jay : public Block {
    public:
        Jay(int x, int y) : Block (x, y, COLOR_JAY, {
            {{1, 0}, {1, 1}, {1, 2}, {0, 2}},
            {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
            {{0, 0}, {0, 1}, {0, 2}, {1, 0}},
            {{2, 1}, {0, 0}, {1, 0}, {2, 0}},
        }) {}
};

class Kay : public Block {
    public:
        Kay(int x, int y) : Block (x, y, COLOR_KAY, {
            {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
            {{0, 0}, {1, 0}, {2, 0}, {0, 1}},
            {{1, 0}, {1, 1}, {1, 2}, {0, 0}},
            {{0, 1}, {1, 1}, {2, 1}, {2, 0}},
        }) {}
};

class Rowling : public Block {
    public:
        Rowling(int x, int y) : Block (x, y, COLOR_ROWLING, {
            {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
            {{1, 0}, {1, 1}, {1, 2}, {0, 1}},
            {{0, 1}, {1, 1}, {2, 1}, {1, 0}},
            {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
        }) {}
};

Block* Block::make(int x, int y) {
    vector<Block> bs = {
        Square(x, y), Line(x, y),
        Harry(x, y), Potter(x, y),
        Jay(x, y), Kay(x, y), Rowling(x, y),
    };
    return new Block(bs[rand() % bs.size()]);
}

bool World::valid(Block &b) {
    for (auto p: b.points()) {
        auto [x, y] = p;
        if (x < 0 || x >= C || y >= R || Bs[y][x]) {
            return false;
        }
    }
    return true;
}

bool World::rotate(Rotation r) {
    Block b(*current);
    b.rotate(r);
    if (!valid(b)) {
        return false;
    }
    current->rotate(r);
    return true;
}

bool World::move(Direction d) {
    Block b(*current);
    b.move(d);
    if (!valid(b)) {
        return false;
    }
    current->move(d);
    return true;
}

bool World::drop() {
    Block b(*current);
    b.drop();
    if (!valid(b)) {
        landed();
        return false;
    }
    current->drop();
    return true;
}

bool World::hard_drop() {
    Block b(*current);
    b.drop();
    while (valid(b)) {
        current->drop();
        b.drop();
    }
    landed();
    return false;
}

int World::check_lines() {
    int ls = 0;
    for (int y = R-1; y >= 0; --y) {
        if (all_of(Bs[y], Bs[y]+C, [](int c) { return c != 0; })) {
            clear_line(y++);
            ls++;
        }
    }
    return ls;
}

bool World::landed() {
    auto color = current->color();
    for (auto p: current->points()) {
        auto [x, y] = p;
        Bs[y][x] = color;
    }
    return true;
}

void World::clear_line(int y) {
    while (y >= 0) {
        for (int x = 0; x < C; ++x) {
            Bs[y][x] = y ? Bs[y-1][x] : 0;
        }
        y--;
    }
}

bool World::spawn() {
    current = Block::make((C-1)/2, 0);
    return valid(*current);
}

WorldView World::render() {
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
