#include <iostream>
#include "domain.h"
#include "usecases.h"
#include "interfaces.h"
#include "infrastructure.h"

using namespace std;

bool again() {
    char c;
    cout << "\nWant to play again? (y/n)\n";
    cin >> c;
    return c == 'y' or c == 'Y';
}

int main() {
    auto seed = time(NULL) * 42;
    srand(seed);
    WithCurses _;
    do {
        HumanPlayer p;
        //RandomPlayer p;
        World w;
        //StreamOutput out(&cout);
        CursesColorOutput out;
        Game g(&p, &w, &out);
        g.start();
    } while (again());
    cout << "seed " << seed << "\n";
}
