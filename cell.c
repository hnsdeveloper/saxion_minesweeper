#include "cell.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Cell {
  size_t bomb_neighbors;  // How many neighbors are bombs.
  bool is_revealed;       // Whether the current Cell is revealed or not.
  bool is_flagged;  // Whether the current Cell is flagged or not. Note, being
                    // revealed takes priority over flagged, as a Cell can't be
                    // both.
  bool is_bomb;     // Whether the current Cell is a bomb.
};

Cell* create_cell_array(size_t element_count) {
  if (element_count > 0) {
    Cell* p = malloc(sizeof(Cell) * element_count);
    if (p) {
      memset(p, 0, element_count * sizeof(Cell));
      return p;
    }
  }
  return NULL;
}

Cell* get_n_element_in_cell_array(Cell* cell_array, size_t n) {
  if (cell_array != NULL) {
    return cell_array + n;
  }
  return NULL;
}

bool is_exploded(Cell* c) { return is_bomb(c) && is_revealed(c); }

bool is_revealed(Cell* c) { return c->is_revealed; }

void set_revealed(Cell* c) {
  c->is_flagged = false;
  c->is_revealed = true;
}

bool is_flagged(Cell* c) { return c->is_flagged; }

void set_flagged(Cell* c) { c->is_flagged = true; }

bool is_bomb(Cell* c) { return c->is_bomb; }

void set_bomb(Cell* c) { c->is_bomb = true; }

void set_bomb_neighbours_count(Cell* c, size_t neighbours) {
  c->bomb_neighbors = neighbours;
}

size_t get_bomb_neighbours_count(Cell* c) { return c->bomb_neighbors; }
