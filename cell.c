#include "cell.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct Cell {
  size_t bomb_neighbors;
  bool is_revealed;
  bool is_flaged;
  bool is_bomb;
};

Cell *create_cell_array(size_t element_count) {
  if (element_count > 0) {
    Cell *p = malloc(sizeof(Cell) * element_count);
    if (p) {
      memset(p, 0, element_count * sizeof(Cell));
      return p;
    }
  }
  return NULL;
}

Cell *get_n_element_in_cell_array(Cell *cell_array, size_t n) {
  if (cell_array != NULL) {
    return cell_array + n;
  }
  return NULL;
}

bool is_exploded(Cell *c) { return is_bomb(c) && is_revealed(c); }

bool is_revealed(Cell *c) { return c->is_revealed; }

void set_revealed(Cell *c) {
  c->is_flaged = false;
  c->is_revealed = true;
}

bool is_flaged(Cell *c) { return c->is_flaged; }

void set_flaged(Cell *c) { c->is_flaged = true; }

bool is_bomb(Cell *c) { return c->is_bomb; }

void set_bomb(Cell *c) { c->is_bomb = true; }

void set_bomb_neighbours_count(Cell *c, size_t neighbours) {
  c->bomb_neighbors = neighbours;
}

size_t get_bomb_neighbours_count(Cell *c) { return c->bomb_neighbors; }
