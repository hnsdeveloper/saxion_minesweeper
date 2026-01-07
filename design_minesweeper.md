# Design of Chess Game (TODO: change title)

**Group members**: Helio Nunes Santos (543793), Kien Nguyen (579399).

This document gives the high-level design of a minesweeper game implementation. It specifies the data structures that are used, the functions the operate on those data structures and describes how the different components interact with each other to implement the minesweeper game.

## Game overview

The game of minesweeper is played on a board of non fixed size, where some spaces (from now on called cells) are empty and some contain bombs. The objective of the game is to either reveal all empty spaces or flag all the bombs. The user only has two different actions in the game, one being revealing a cell, which reveal neighbor cells that are empty and stops when a neighbor cell is a bomb, or flaging. When all empty spaces are revealed or all the bombs are flagged, the game ends with the player winning, otherwise, when the player reveals a spot where there is a bomb, it ends with the player losing. The first user action is always a safe action, thus if the player reveals, it will reveal the cell and all empty ones around. If the player flags, the player will have flagged an empty Cell.

## Design components

The following "entities" will be used to represent the game state:

- `Board`: Represents the game board, where there are different `Cells`.
- `Cell` : Represents one of the cells in a board, holding state such as if it is a bomb, if it is revealed, if it is flagged and how many of it neighbors are bombs.
- `Action` : Represents an action that will be applied on the board, such as revealing a `Cell` or flaging one.
- `Coordinate` : Represents a coordinate where an `Action` will be applied.

### Data Structures and enumerations

#### Board

A board is represented by the following structure:

```c
struct Board {
  size_t width; // The width of the board.
  size_t height; // The height of the board.
  size_t bomb_count; // How many Cells are bombs in the board.
  size_t correctly_flagged_bombs; // How many Cells have been correctly flagged as bombs.
  size_t revealed_count; // How many Cells were revealed in total.
  Cell *board_layout; // An array of Cells with size width * height.
  bool is_lose; // Boolean stating whether there is a lose condition.
};
```

#### Cell

```c
struct Cell {
  size_t bomb_neighbors; // How many neighbors are bombs.
  bool is_revealed; // Whether the current Cell is revealed or not.
  bool is_flagged; // Whether the current Cell is flagged or not. Note, being revealed takes priority over flagged, as a Cell can't be both.
  bool is_bomb; // Whether the current Cell is a bomb.
};
```

#### Action

```c
struct Action {
  Coordinate *coordinate; // A coordinate where such action should be applied
  bool is_flag; // Whether the action is a flagging action. Note that !is_flag == is_reveal.
};
```

#### Coordinate

```c
struct Coordinate {
  size_t x; // The x component of the Coordinate.
  size_t y; // The y component of the Coordinate.
};
```

## Interaction between components

At the highest level, the `main` function would look like this (pseudocode):

```
main
    display_welcome_message()
    while true 
        display_board_setup_prompt()
        x, y = collect_board_width_height_from_user()
        // If either x or y are zero, it would make it impossible to play, thus we end the game
        if x == 0 || y == 0 
            break
        Board b =: create_board(x, y)
        while !b.is_game_over()
            Action a =: get_action_from_user_input()
            // Apply action should process which Cells to reveal or flag
            b.apply_action(a)
            // After an action is applied, the board determines if a winning or lose condition happened
        
        if b.is_win()
            display_win_message()
        elif b.is_lose()
            display_lose_message()
end
```

Checking for game over condition is handled on the main loop. Displaying the board is handled by its respective function, as applying an `Action` to the board also is. The most complex function is the `reveal_recursive` function, which uses the flood fill algorithm (implemented recursively) to reveal neighboring cells when the player clicks on an empty `Cell`. The code also possesses functions for handling gathering user input, which will not be further detailed as they do not consist a part of the game itself and could be easily replaced for whichever implementation of choice. 

An interface for drawing can be provided to the Board, as currently the way it is drawn is tightly coupled with itself (i.e. the board draws itself). Given that the project allows for the use of external libraries, it would be interesting to allow it to be drawn in the console and on a GUI. For this, it would require a new struct/object `Drawer` and the board would have an interface for drawing in the form `void draw_board(Board* b, Drawer* d)`, such that `Drawer` is a struct holding different function pointers and a void* data pointer. The `draw_board` function would then call the methods of the `Drawer` struct to guide it on drawing. If time allows it will be implemented and as such, the drawing interface will be commented out on the `board.h` file.


## Header files

#### board.h

```c
#ifndef _BOARD_H_
#define _BOARD_H_

#include "action.h"
#include <stdbool.h>
#include <stddef.h>

typedef struct Board Board;

/// @brief Creates a board to play the game.
/// @param x The width of the board.
/// @param y The height of the board.
/// @return A pointer to a board on success, or a null pointer on failure.
Board *create_board(size_t x, size_t y);

/// @brief Destroys a board, deallocating it and whichever objects it uses.
/// @param board The board to be destroyed.
void destroy_board(Board *board);

/// @brief Draws a board.
/// @param board The board to be drawn.
void draw_board(Board *board);

/// @brief Draws a board using a Drawer
/// @param board The board to be drawn.
/// @param drawer The drawer.
/// Commented out as it will be used to draw a GUI only if time allows it.
// void draw_board(Board* board, Drawer* drawer)

/// @brief Applies an action to the board.
/// @param board The board to where the action will be applied.
/// @param action The action to be applied.
void apply_action_on_board(Board *board, Action *action);

/// @brief Checks if a loosing condition has been reached.
/// @param board The board to which it will be checked.
/// @return True if a loosing condition has been reached, otherwise false.
bool is_lose_condition(Board *board);

/// @brief Check if a winning condition has been reached.
/// @param board The board to which it will be checked.
/// @return True if a winning condition has been reached, otherwise false.
bool is_win_condition(Board *board);

/// @brief Gets the board width
/// @param board The board which we will check
/// @return The board width
size_t get_board_width(Board *board);

/// @brief Gets the board height
/// @param board The board which we will check
/// @return The board height
size_t get_board_height(Board *board);

#ifdef MINESWEEPER_DEBUG
    void draw_board_debug(Board *board);
#endif

#endif
```

#### cell.h

```c
#ifndef _CELL_H_
#define _CELL_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct Cell Cell;

/// @brief Creates a cell array with element_count elements.
/// @param element_count How many elements the array should have.
/// @return A pointer to the first element of the array or NULL if failed.
Cell *create_cell_array(size_t element_count);

/// @brief Gets the n element of a Cell array.
/// @param cell_array The cell array.
/// @param n The index of the element
/// @return A pointer to the element
Cell *get_n_element_in_cell_array(Cell *cell_array, size_t n);

/// @brief Checks if a cell is exploded after an user action.
/// @param c The cell which will be checked.
/// @return True if it has exploded, false if not.
bool is_exploded(Cell *c);

/// @brief Tells if a Cell is already revealed or not.
/// @param c The Cell that will be checked.
/// @return True if it is revealed, otherwise false.
bool is_revealed(Cell *c);

/// @brief Sets a Cell as revealed. Revealed has priority over flagged.
/// @param c The cell to set.
void set_revealed(Cell *c);

/// @brief Tells if a Cell is flagged or not.
/// @param c The Cell that will be checked.
/// @return True if it is flagged, otherwise false.
bool is_flagged(Cell *c);

/// @brief Sets a Cell as flagged.
/// @param c The cell to set.
void set_flagged(Cell *c);

/// @brief Tells if a Cell is a bomb.
/// @param c The cell to which it will be checked
/// @return True if it is a bomb, false if it is not
bool is_bomb(Cell *c);

/// @brief Sets a Cell as a bomb.
/// @param c The cell to be set.
void set_bomb(Cell *c);

/// @brief Sets the cell neighbour bomb count.
/// @param c The cell to set it.
/// @param neighbours The cell neighbour count that are bombs.
void set_bomb_neighbours_count(Cell *c, size_t neighbours);

/// @brief Gets how many neighbours of this cell are bombs
/// @param c The cell which it will be checked
/// @return The amount of neighbours that are bombs
size_t get_bomb_neighbours_count(Cell *c);

#endif
```

#### action.h

```c
#ifndef _ACTION_H_
#define _ACTION_H_

#include "coordinate.h"
#include <stdbool.h>

typedef struct Action Action;

/// @brief Creates a reveal action on coordinates (X, Y)
/// @param x The x coordinate
/// @param y The y coordinate
/// @return The action
Action *create_reveal_action(Coordinate *coordinate);

/// @brief Creates a flag action on coordinates (X, Y)
/// @param x The x coordinate
/// @param y The y coordinate
/// @return
Action *create_flag_action(Coordinate *coordinate);

/// @brief Gets the x component from an action
/// @param action The action to which we want to query the x component
/// @return The x component of the action
size_t action_get_x(Action *action);

/// @brief Gets the y component from an action
/// @param action The action to which we want to query the y component
/// @return The y component of the action
size_t action_get_y(Action *action);

/// @brief Tells if an action is a reveal action
/// @param action The action
/// @return True if it is a reveal action, false otherwise
bool is_reveal(Action *action);

/// @brief Tells if an action is a flag action
/// @param action The action
/// @return True if it is a flag action, false otherwise
bool is_flag(Action *action);

/// @brief Destroys an action, deallocating its memory
/// @param action The action to be deallocated
void destroy_action(Action *action);

#endif
```

#### coordinate.h

```c
#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <stddef.h>

typedef struct Coordinate Coordinate;

/// @brief Creates a coordinate.
/// @param x The x component.
/// @param y The y component.
/// @return A coordinate on success, NULL on failure.
Coordinate *create_coordinate(size_t x, size_t y);

/// @brief Gets the x component from a coordinate
/// @param coordinate The coordinate
/// @return The x component of the coordinate
size_t coordinate_get_x(Coordinate *coordinate);

/// @brief Gets the y component from a coordinate
/// @param coordinate The coordinate
/// @return The y component of the coordinate
size_t coordinate_get_y(Coordinate *coordinate);

/// @brief Destroys (deallocates) a coordinate.
/// @param coordinate The coordinate to be deallocated.
void destroy_coordinate(Coordinate *coordinate);

#endif
```
