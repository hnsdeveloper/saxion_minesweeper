#ifndef _BOARD_H_
#define _BOARD_H_

#include <stddef.h>
#include "action.h"

typedef struct Board Board;

/// @brief Creates a board to play the game.
/// @param x The width of the board.
/// @param y The height of the board.
/// @return A pointer to a board on success, or a null pointer on failure.
Board* create_board(size_t x, size_t y);

/// @brief Destroys a board, deallocating it and whichever objects it uses.
/// @param board The board to be destroyed.
void destroy_board(Board* board);

/// @brief Draws a board.
/// @param board The board to be drawn.
void draw_board(Board* board);

/// @brief Applies an action to the board.
/// @param action The action to be applied.
/// @param board The board to where the action will be applied.
void apply_action_on_board(Action* action, Board* board);

bool is_loose_condition(Board* board);


#endif