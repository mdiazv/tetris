#include <iostream>
#include "domain.h"
#include "usecases.h"
#include "interfaces.h"
#include "infrastructure.h"

using namespace std;

int main() {
    auto seed = time(NULL) * 42;
    srand(seed);
    WithCurses _;
    HumanPlayer p;
    //RandomPlayer p;
    World w;
    //StreamOutput out(&cout);
    CursesColorOutput out;
    Game g(&p, &w, &out);
    g.start();
    cout << "seed " << seed << "\n";
}
