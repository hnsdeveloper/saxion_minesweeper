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

size_t action_get_x(Action *action);

size_t action_get_y(Action *action);

bool is_reveal(Action *action);

bool is_flag(Action *action);

void destroy_action(Action *action);

#endif
