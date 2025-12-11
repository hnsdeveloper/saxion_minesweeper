#ifndef _CELL_H_
#define _CELL_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct Cell Cell;

/// @brief Creates a cell array with element_count elements.
/// @param element_count How many elements the array should have.
/// @return A pointer to the first element of the array or NULL if failed.
Cell* create_cell_array(size_t element_count);

/// @brief Gets the n element of a Cell array.
/// @param cell_array The cell array.
/// @param n The index of the element
/// @return A pointer to the element
Cell* get_n_element_in_cell_array(Cell* cell_array, size_t n);

/// @brief Checks if a cell is exploded after an user action.
/// @param c The cell which will be checked.
/// @return True if it has exploded, false if not.
bool is_exploded(Cell* c);

/// @brief Sets a Cell as revealed. Revealed has priority over flaged.
/// @param c The cell to set.
void set_revealed(Cell* c);

/// @brief Sets a Cell as flagged.
/// @param c The cell to set.
void set_flaged(Cell* c);

/// @brief Sets a Cell as a bomb.
/// @param c The cell to be set.
void set_bomb(Cell* c);

/// @brief Sets the cell neighbour bomb count.
/// @param c The cell to set it.
/// @param neighbours The cell neighbour count that are bombs.
void set_bomb_neighbours_count(Cell* c, size_t neighbours);

#endif