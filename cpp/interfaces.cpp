#include "interfaces.h"

void StreamOutput::render(World &w) {
    auto v = w.render();
    for (auto row : v) {
        *out << " | ";
        for (auto c : row) {
            *out << c << " ";
        }
        *out << "|\n";
    }
    *out << " | ";
    for (int i = 0; i < v[0].size(); ++i) {
        *out << "- ";
    }
    *out << "|\n";
}
