#include "cell.h"
#include "board.h"
#include "action.h"
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

struct Board {
    size_t width;
    size_t height;
    size_t bomb_count;
    size_t revealed_count;
    Cell* board_layout;
    bool is_lose;
};

Board* create_board(size_t x, size_t y) {
    Board* p = malloc(x * y * sizeof(Board));
    if (p) {
        Cell* c = create_cell_array(x*y);
        if(c != NULL) {
            p->width = x;
            p->height = y;
            p->bomb_count = 0;
            p->revealed_count = 0;
            p->board_layout = c;
            p->is_lose = false;
            return p;
        }
        free(p);
    }

    return NULL;
}

size_t reveal_recursive(Board* board, size_t x, size_t y, bool first) {
    // So we have 8 neighbors, we must check them all if they can be revealed
    
    size_t idx = board->height * y + x;
    Cell* self = get_n_element_in_cell_array(board->board_layout, idx);
    if((is_revealed(self) && !first) || is_bomb(self)) {
        return 0;
    }

    set_revealed(self);
    size_t acc = 1;

    size_t begin = x > 0 ? x - 1 : x;
    size_t end = x < board->width - 1 ? x + 1 : x;

    for(size_t i = 0; i < end - begin + 1; ++i) {
        // Top ones
        if(y > 0) {        
            acc += reveal_recursive(board, begin + i, y - 1, false);
        }
        // Same row, excluding self
        if(begin + i != x) {
            acc += reveal_recursive(board, begin + i, y, false);
        }
        // Bottom ones
        if(y < board->height - 1) {
            acc += reveal_recursive(board, begin + i, y + 1, false);
        }    
    }
    
    return acc;
}

/// @brief Fills the board based on the first action of the player. We need to do like this to guarantee that the first
/// action is safe and doesn't cause a game over.
/// @param board The board to be filled
/// @param action The player action
void fill_board(Board* board, Action* action) {
    static bool is_seeded = false;

    if(!is_seeded) {
        srand(time(NULL));
        is_seeded = true;
    }

    size_t bomb_count = 0;
    for(size_t i = 0; i < board->height; ++i) {
        for(size_t j = 0; j < board->width; ++j) {        
            Cell* c = get_n_element_in_cell_array(board->board_layout, board->height * i + j);
            if (get_y(action) == i && get_x(action) == j) {
                continue;
            }
            int r = rand();
            if(r % 2 == 0) {
                set_bomb(c);
                ++bomb_count;
            }
        }
    }

    board->bomb_count = bomb_count;
}

void apply_action_on_board(Board* board, Action* action) {
    // For when we initialize the board, its bomb count will be 0,
    // thus we keep looping until it is not zero anymore
    while(board->bomb_count == 0) {
        fill_board(board, action);
    }
        
    size_t x = get_x(action) - 1;
    size_t y = get_y(action) - 1;
    size_t idx = board->height * y + x;
    Cell* selected_cell = get_n_element_in_cell_array(board->board_layout, idx);
    
    if(is_flag(action)) {
        set_flaged(selected_cell);
    } else {
        if (!is_revealed(selected_cell)) {
            set_revealed(selected_cell);
            if(is_exploded(selected_cell)) {
                board->is_lose = true;
                return;
            }
            board->revealed_count += 1 + reveal_recursive(board, x, y, true);
        }
    } 
}

bool is_loose_condition(Board* board) {
   return board->is_lose;
}

bool is_win_condition(Board* board) {
    const size_t total_cells = board->width * board->height;
    const size_t must_reveal = total_cells - board->bomb_count;
    return must_reveal == board->revealed_count;
}

void destroy_board(Board* board) {
    if(board) {
        if(board->board_layout)
            free(board->board_layout);
        free(board);
    }
}

void draw_board(Board* board) {
    for(size_t i = 0; i < board->height; ++i) {
        if (i == 0) {
            for(size_t j = 0; j < board->width; ++j) {
                if(j == 0) 
                    printf("\n%4c", 0);
                
                printf("[%zu]%c", j, j < board->width - 1 ? ' ' : 0);
            }
        }
        for(size_t j = 0; j < board->width; ++j) {
            if(j == 0) {
                printf("\n%4zu ", i + 1);
            }

            size_t idx = i * board->height + j;
            Cell* cell = get_n_element_in_cell_array(board->board_layout, idx);
            char c;
            if(is_revealed(cell)) {
                if(get_bomb_neighbours_count(cell) > 0) {
                    c = '0' + get_bomb_neighbours_count(cell);
                } else if (is_bomb(cell)) {
                    // For when there is a game over.
                    c = 'X';
                } else {
                    c = 'S';
                }
            } else if(is_flaged(cell)) {
                c = 'F';
            } else {
                c = 0x20;
            }

            printf("[%c]%c",c, j < board->width - 1 ? ' ' : 0);
            
        }
    }
}


