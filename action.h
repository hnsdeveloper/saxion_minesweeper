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
