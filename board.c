#include "board.h"
#include "action.h"
#include "cell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Board {
  size_t width;
  size_t height;
  size_t bomb_count;
  size_t correctly_flagged_bombs;
  size_t revealed_count;
  Cell *board_layout;
  bool is_lose;
};

Board *create_board(size_t x, size_t y) {
  Board *p = malloc(x * y * sizeof(Board));
  if (p) {
    Cell *c = create_cell_array(x * y);
    if (c != NULL) {
      p->width = x;
      p->height = y;
      p->bomb_count = 0;
      p->revealed_count = 0;
      p->board_layout = c;
      p->is_lose = false;
      p->correctly_flagged_bombs = 0;
      return p;
    }
    free(p);
  }

  return NULL;
}

size_t reveal_recursive(Board *board, size_t x, size_t y, bool first) {
  // So we have 8 neighbors, we must check them all if they can be revealed
  size_t idx = board->width * y + x;

  Cell *self = get_n_element_in_cell_array(board->board_layout, idx);
  if ((is_revealed(self) && !first)) {
    return 0;
  }

  set_revealed(self);
  size_t acc = 1;

  size_t begin = x > 0 ? x - 1 : x;
  size_t end = x < board->width - 1 ? x + 1 : x;

  size_t bomb_neighbors_count = 0;

  // If this was C++ I would just use a lambda to not have to repeat the loop
  // code twice :p
  for (size_t i = 0; i < end - begin + 1; ++i) {
    // Top ones
    if (y > 0) {
      size_t top_idx = (y - 1) * board->width + begin + i;
      Cell *c = get_n_element_in_cell_array(board->board_layout, top_idx);
      bomb_neighbors_count += is_bomb(c) ? 1 : 0;
    }
    // Same row, excluding self
    if (begin + i != x) {
      size_t same_line_idx = y * board->width + begin + i;
      Cell *c = get_n_element_in_cell_array(board->board_layout, same_line_idx);
      bomb_neighbors_count += is_bomb(c) ? 1 : 0;
    }
    // Bottom ones
    if (y < board->height - 1) {
      size_t bottom_idx = (y + 1) * board->width + begin + i;
      Cell *c = get_n_element_in_cell_array(board->board_layout, bottom_idx);
      bomb_neighbors_count += is_bomb(c) ? 1 : 0;
    }
  }

  set_bomb_neighbours_count(self, bomb_neighbors_count);

  if (bomb_neighbors_count == 0) {
    for (size_t i = 0; i < end - begin + 1; ++i) {
      // Top ones
      if (y > 0) {
        acc += reveal_recursive(board, begin + i, y - 1, false);
      }
      // Same row, excluding self
      if (begin + i != x) {
        acc += reveal_recursive(board, begin + i, y, false);
      }
      // Bottom ones
      if (y < board->height - 1) {
        acc += reveal_recursive(board, begin + i, y + 1, false);
      }
    }
  }

  return acc;
}

/// @brief Fills the board based on the first action of the player. We need to
/// do like this to guarantee that the first action is safe and doesn't cause a
/// game over.
/// @param board The board to be filled
/// @param action The player action
void fill_board(Board *board, Action *action) {
  static bool is_seeded = false;

  if (!is_seeded) {
    srand(time(NULL));
    is_seeded = true;
  }

  size_t bomb_count = 0;
  for (size_t i = 0; i < board->height; ++i) {
    for (size_t j = 0; j < board->width; ++j) {
      if (action_get_y(action) == i && action_get_x(action) == j) {
        continue;
      }
      Cell *c = get_n_element_in_cell_array(board->board_layout,
                                            board->width * i + j);
      int r = rand();
      if (r % 3 == 0) {
        set_bomb(c);
        ++bomb_count;
      }
    }
  }

  board->bomb_count = bomb_count;
}

void apply_action_on_board(Board *board, Action *action) {
  // For when we initialize the board, its bomb count will be 0,
  // thus we keep looping until it is not zero anymore (or everything is filled
  // with bombs, as it wouldn't be possible to play).
  while (board->bomb_count == 0 ||
         board->bomb_count == (board->width * board->height)) {
    fill_board(board, action);
  }

  size_t x = action_get_x(action);
  size_t y = action_get_y(action);
  size_t idx = board->width * y + x;
  Cell *selected_cell = get_n_element_in_cell_array(board->board_layout, idx);

  if (is_reveal(action)) {
    if (!is_revealed(selected_cell)) {
      if (is_bomb(selected_cell)) {
        set_revealed(selected_cell);
        board->is_lose = true;
        return;
      }
      board->revealed_count += reveal_recursive(board, x, y, true);
    }
  } else if (is_flag(action)) {
    if (is_revealed(selected_cell))
      return;
    if (!is_flaged(selected_cell)) {
      set_flaged(selected_cell);
      if (is_bomb(selected_cell))
        board->correctly_flagged_bombs += 1;
    }
  }
}

bool is_lose_condition(Board *board) { return board->is_lose; }

bool is_win_condition(Board *board) {
  const size_t total_cells = board->width * board->height;
  const size_t must_reveal = total_cells - board->bomb_count;
  return must_reveal == board->revealed_count ||
         (board->bomb_count == 0
              ? false
              : board->correctly_flagged_bombs == board->bomb_count);
}

void destroy_board(Board *board) {
  if (board) {
    if (board->board_layout)
      free(board->board_layout);
    free(board);
  }
}

void draw_board(Board *board) {
  for (size_t i = 0; i < board->height; ++i) {
    if (i == 0) {
      for (size_t j = 0; j < board->width; ++j) {
        if (j == 0)
          printf("\n     ");

        printf("%3zu%c", j + 1, j < board->width - 1 ? ' ' : 0);
      }
    }
    for (size_t j = 0; j < board->width; ++j) {
      if (j == 0) {
        printf("\n%4zu ", i + 1);
      }

      size_t idx = i * board->width + j;
      Cell *cell = get_n_element_in_cell_array(board->board_layout, idx);
      char c;
      if (is_revealed(cell)) {
        if (get_bomb_neighbours_count(cell) > 0) {
          c = '0' + get_bomb_neighbours_count(cell);
        } else if (is_bomb(cell)) {
          // For when there is a game over.
          c = 'X';
        } else {
          c = 'R';
        }
      } else if (is_flaged(cell)) {
        c = 'F';
      } else {
        c = 0x20;
      }

      printf("[%c]%c", c, j < board->width - 1 ? ' ' : 0);
    }
  }
  printf("\n");
}

size_t get_board_width(Board *board) { return board->width; }

size_t get_board_height(Board *board) { return board->height; }

#ifdef MINESWEEPER_DEBUG
void draw_board_debug(Board *board) {
  for (size_t i = 0; i < board->height; ++i) {
    if (i == 0) {
      for (size_t j = 0; j < board->width; ++j) {
        if (j == 0)
          printf("\n     ");

        printf("%3zu%c", j + 1, j < board->width - 1 ? ' ' : 0);
      }
    }
    for (size_t j = 0; j < board->width; ++j) {
      if (j == 0) {
        printf("\n%4zu ", i + 1);
      }

      size_t idx = i * board->width + j;
      Cell *cell = get_n_element_in_cell_array(board->board_layout, idx);
      char c;

      if (is_bomb(cell)) {
        c = 'X';
      } else if (is_revealed(cell)) {
        if (get_bomb_neighbours_count(cell) > 0) {
          c = '0' + get_bomb_neighbours_count(cell);
        } else {
          c = 'R';
        }
      } else {
        c = 'E';
      }

      printf("[%c]%c", c, j < board->width - 1 ? ' ' : 0);
    }
  }

  printf("\nBomb count: %zu", board->bomb_count);
  printf("\n");
}
#endif