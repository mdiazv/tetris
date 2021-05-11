#include <iostream>
#include "domain.h"
#include "usecases.h"
#include "interfaces.h"

using namespace std;

int main() {
    auto seed = time(NULL) * 42;
    srand(seed);
    HumanPlayer p;
    //RandomPlayer p;
    World w;
    //StreamOutput out(&cout);
    CursesOutput out;
    Game g(&p, &w, &out);
    g.start();
    cout << "seed " << seed << "\n";
}
