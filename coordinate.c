#include "coordinate.h"
#include <stdlib.h>

struct Coordinate {
  size_t x; // The x component of the Coordinate.
  size_t y; // The y component of the Coordinate.
};

Coordinate *create_coordinate(size_t x, size_t y) {
  Coordinate *p = malloc(sizeof(Coordinate));
  if (p) {
    p->x = x;
    p->y = y;
    return p;
  }
  return NULL;
}

/// @brief Gets the x component from a coordinate
/// @param coordinate The coordinate
/// @return The x component of the coordinate
size_t coordinate_get_x(Coordinate *coordinate) { return coordinate->x; }

/// @brief Gets the y component from a coordinate
/// @param coordinate The coordinate
/// @return The y component of the coordinate
size_t coordinate_get_y(Coordinate *coordinate) { return coordinate->y; }

void destroy_coordinate(Coordinate *coordinate) { free(coordinate); }