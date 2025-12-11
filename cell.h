#ifndef _CELL_H_
#define _CELL_H_

#include <stdbool.h>

typedef struct Cell Cell;

Cell* get_n_element_in_cell_array(Cell* cell_array);
bool is_exploded(Cell* c);

#endif