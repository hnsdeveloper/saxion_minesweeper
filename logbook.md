# Logbook

**Group 2 members**: Helio Nunes Santos (543793), Kien Nguyen (579399).

## Description of functions implemented by Helio

### main.c
```c
int main();
```

### board.c

```c
Board* create_board(size_t x, size_t y);
size_t reveal_recursive(Board* board, size_t x, size_t y, bool first);
void fill_board(Board* board, Action* action);
void apply_action_on_board(Board* board, Action* action);
bool is_lose_condition(Board* board);
bool is_win_condition(Board* board);
void destroy_board(Board* board);
void draw_board(Board* board);
size_t get_board_width(Board* board);
size_t get_board_height(Board* board);
void draw_board_debug(Board* board);
```
### input.c

```c
size_t next_pow2(size_t value);
int dynamic_buffer_pow_two(char** buffer, size_t* size);
int read_line_from_file(FILE* file, char** target);
char* read_input_from_stdin();
size_t read_size_t_stdin();
```
### Makefile

```
All targets written by Helio
```

## Description of functions implemented by Kien

### action.c
```c
Action* create_reveal_action(Coordinate* coordinate);
Action* create_flag_action(Coordinate* coordinate);
size_t action_get_x(Action* action);
size_t action_get_y(Action* action);
bool is_reveal(Action* action);
bool is_flag(Action* action);
void destroy_action(Action* action);
```

### cell.c
```c
Cell* create_cell_array(size_t element_count);
Cell* get_n_element_in_cell_array(Cell* cell_array, size_t n);
bool is_exploded(Cell* c);
bool is_revealed(Cell* c);
void set_revealed(Cell* c);
bool is_flagged(Cell* c);
void set_flagged(Cell* c);
bool is_bomb(Cell* c);
void set_bomb(Cell* c);
void set_bomb_neighbours_count(Cell* c, size_t neighbours);
size_t get_bomb_neighbours_count(Cell* c);
```

### coordinate.c

```c
Coordinate* create_coordinate(size_t x, size_t y);
size_t coordinate_get_x(Coordinate* coordinate);
size_t coordinate_get_y(Coordinate* coordinate);
void destroy_coordinate(Coordinate* coordinate);
```

## Changes that occurred during development

No changes in the project structure ocurred as we had the project done before discussion with the teachers regarding the design. As such no changes were needed. After presenting the project to the teachers, only some bug fixes were made. Also a limitation on the size of the grid has been imposed, as allowing for unlimited side sizes for the grid would cause overflow when calculating how many bytes are needed to allocate for the cells, or, if not causing an overflow in the calculations, could cause the process to request too much memory to the OS, which in turn would kill the process due to OOM or cause allocation failures. 