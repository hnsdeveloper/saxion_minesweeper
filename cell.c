#include "cell.h"
#include <stddef.h>

struct Cell {
    size_t bomb_neighbors;
    bool is_revealed;
    bool is_bomb;
};

bool is_exploded(Cell* c) {
    return c->is_bomb && c->is_revealed;
}

