#include "action.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Action {
  Coordinate *coordinate; // A coordinate where such action should be applied
  bool is_flag; // Whether the action is a flagging action. Note that !is_flag == is_reveal.
};

Action *create_reveal_action(Coordinate *coordinate) {
  Action *p = create_flag_action(coordinate);
  p->is_flag = false;
  return p;
}

Action *create_flag_action(Coordinate *coordinate) {
  Action *p = malloc(sizeof(Action));
  p->coordinate = coordinate;
  p->is_flag = true;
  return p;
}

size_t action_get_x(Action *action) {
  return coordinate_get_x(action->coordinate);
}

size_t action_get_y(Action *action) {
  return coordinate_get_y(action->coordinate);
}

bool is_reveal(Action *action) { return !is_flag(action); }

bool is_flag(Action *action) { return action->is_flag; }

void destroy_action(Action *action) { free(action); }
