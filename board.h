#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdbool.h>
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
/// @param board The board to where the action will be applied.
/// @param action The action to be applied.
void apply_action_on_board(Board* board, Action* action);

/// @brief Checks if a loosing condition has been reached.
/// @param board The board to which it will be checked.
/// @return True if a loosing condition has been reached, otherwise false.
bool is_lose_condition(Board* board);

/// @brief Check if a winning condition has been reached.
/// @param board The board to which it will be checked.
/// @return True if a winning condition has been reached, otherwise false.
bool is_win_condition(Board* board);

/// @brief Gets the board width
/// @param board The board which we will check
/// @return The board width
size_t get_board_width(Board* board);

/// @brief Gets the board height
/// @param board The board which we will check
/// @return The board height
size_t get_board_height(Board* board);

#ifdef MINESWEEPER_DEBUG
void draw_board_debug(Board* board);
#endif

#endif