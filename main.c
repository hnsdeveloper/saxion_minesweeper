#include "board.h"
#include "input.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("Welcome to Minesweeper.\n"
         "The game will show you a grid with cells.\n"
         "On each of these cells there might be a bomb or not. Through console "
         "input you will decide\non actions (revealing a cell or flagging it). "
         "Revealing might reveal adjacent cells.\n"
         "Cells revealed will show the an R or the number of neighbor bombs. "
         "Cells not revealed will contain nothing.\n"
         "Attempting to flag an already revealed cell produces no effect\n"
         "To win, either reveal all the cells that contain no bombs or flag "
         "all bombs.\nGood luck!\n");

  while (true) {
    printf("Please, provide a width to play (0 will end the game) : ");
    size_t width = read_size_t_stdin();

    printf("Please, provide a height to play (0 will end the game) : ");
    size_t height = read_size_t_stdin();

    if (width == 0 || height == 0) {
      break;
    }

    Board *b = create_board(width, height);
    draw_board(b);
    while (!is_lose_condition(b) && !is_win_condition(b)) {
      printf("Please provide an action in the format '($X, $Y, $ACTION)' where "
             "X and Y are positive integers\nwithin boundaries and ACTION is "
             "either 'R' for reveal and 'F' for flag : ");
      char *input = read_input_from_stdin();
      size_t x;
      size_t y;
      char action[2];
      char c[2];

      int r = sscanf(input, "%1[(] %zu %1[,] %zu %1[,] %1[RrFf] %1[)] %c", c,
                     &x, c, &y, c, action, c, c);
      free(input);

      if (r != 7 || x == 0 || x > get_board_width(b) || y == 0 ||
          y > get_board_height(b)) {
        printf("Invalid input. Try again.\n");
        continue;
      }

      Action *act = NULL;
      if (((action[0] | 0x20) ^ 0x20) == 'R') {
        act = create_reveal_action(create_coordinate(x - 1, y - 1));
      } else {
        act = create_flag_action(create_coordinate(x - 1, y - 1));
      }

      apply_action_on_board(b, act);
      destroy_action(act);
#ifdef MINESWEEPER_DEBUG
      draw_board_debug(b);
#endif
      draw_board(b);
    }

    if (is_win_condition(b)) {
      printf("Congrats, you won this match!\n");
    } else {
      printf("Oh, so sad :(. You lost. Better luck next time.\n");
    }

    destroy_board(b);
  }

  return 0;
}
