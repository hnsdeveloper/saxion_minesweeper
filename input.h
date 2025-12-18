#ifndef _INPUT_H_
#define _INPUT_H_

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/// @brief Reads input from stdin, up to a new line character.
/// @return An allocated string containing the input from stdin without the
/// newline character.
char* read_input_from_stdin();

/// @brief Reads a size_t from stdin.
/// @return The value read.
size_t read_size_t_stdin();

#endif