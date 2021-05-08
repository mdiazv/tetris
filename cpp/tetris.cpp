#include <iostream>
#include <unistd.h>
#include "domain.h"
#include "interfaces.h"

using namespace std;

int main() {
    srand(time(NULL));
    for (int k = 0; k < 10; k++) {
        Block b = *Block::make(0, 0);
        for (auto p : b.points()) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << "\n";
        b.rotate(ROTATE_CW);
        for (auto p : b.points()) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << "\n";
    }
    StreamOutput out(&cout);
    World w;
    w.spawn();
    out.render(w);
    for (int i = 0; i < 15; i++) {
        usleep(500000);
        w.drop();
        out.render(w);
    }
}
