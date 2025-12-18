#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <stddef.h>

typedef struct Coordinate Coordinate;

/// @brief Creates a coordinate.
/// @param x The x component.
/// @param y The y component.
/// @return A coordinate on success, NULL on failure.
Coordinate* create_coordinate(size_t x, size_t y);

/// @brief Gets the x component from a coordinate
/// @param coordinate The coordinate
/// @return The x component of the coordinate
size_t coordinate_get_x(Coordinate* coordinate);

/// @brief Gets the y component from a coordinate
/// @param coordinate The coordinate
/// @return The y component of the coordinate
size_t coordinate_get_y(Coordinate* coordinate);

/// @brief Destroys (deallocates) a coordinate.
/// @param coordinate The coordinate to be deallocated.
void destroy_coordinate(Coordinate* coordinate);

#endif