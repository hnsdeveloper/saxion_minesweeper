#include "cell.h"
#include "board.h"
#include "action.h"
#include <stdbool.h>

struct Board {
    size_t width;
    size_t height;
    Cell* board_layout;
};

/// @brief Creates a board to play the game.
/// @param x The width of the board.
/// @param y The height of the board.
/// @return A pointer to a board on success, or a null pointer on failure.
Board* create_board(size_t x, size_t y) {
    Board* p = malloc(x * y * sizeof(Board));
    if (p) {
        Cell* c = create_cell_array(x*y);
        if(c != NULL) {
            p->width = x;
            p->height = y;
            return p;
        }
        free(p);
    }

    return NULL;
}

/// @brief Fills the board based on the first action of the player. We need to do like this to guarantee that the first
/// action is safe and doesn't cause a game over.
/// @param board The board to be filled
/// @param action The player action
void fill_board(Board* board, Action* action) {
    for(size_t i = 0; i < board->height; ++i) {
        for(size_t j = 0; j < board->width; ++j) {
            if()
            
            Cell* c = get_n_element_in_cell_array(board->board_layout, board->height * i + j);
            
        }
    }
}

bool is_loose_condition(Board* board) {
    for(size_t i = 0; i < board->height; ++i) {
        for(size_t j = 0; j < board->width; ++j) {
            Cell* c = get_n_element_in_cell_array(board->height * i + j);
            if(is_exploded(c)) {
                return true;
            }
        }
    }
}

void destroy_board(Board* board) {
    if(board) {
        if(board->board_layout)
            free(board->board_layout);
        free(board);
    }
}

