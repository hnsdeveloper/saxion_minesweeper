#include "cell.h"
#include "board.h"
#include <stdbool.h>

struct Board {
    size_t width;
    size_t height;
    Cell* board_layout;
};

/// @brief Fills the board based on the first action of the player
/// @param board The board to be filled
void fill_board(Board* board) {
    for(size_t i = 0; i < board->height; ++i) {
        for(size_t j = 0; j < board->width; ++j) {
            Cell* c = get_n_element_in_cell_array(board->height * i + j);
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

