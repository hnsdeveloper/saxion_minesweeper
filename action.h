#ifndef _ACTION_H_
#define _ACTION_H_

typedef struct Action Action;

Action* create_reveal_action(size_t x, size_t y);

Action* create_flag_action(size_t x, size_t y);

size_t get_x(Action* action);

size_t get_y(Action* action);

bool is_reveal(Action* action);

bool is_flag(Action* action);

void destroy_action(Action* action);


#endif
