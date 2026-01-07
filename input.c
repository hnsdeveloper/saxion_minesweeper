#include "input.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  SUCCESS = 0,
  INVALID_ARGUMENTS,
  ALLOCATION_FAILURE,
  FILE_ERROR,
  END_OF_FILE  // EOF already exists, and it could be anything, so we define
               // it again (with a different name)
} Error;

size_t next_pow2(size_t value) {
  size_t i = 1;
  while (i <= value) {
    i = i << 1;
    if (i == 0) break;
  }

  return i;
}

/// @brief Increases a buffer in power of 2 sizes. If a NULL buffer with size 0
/// is given, allocates a 2^0 buffer.
/// @param buffer A pointer to where the pointer to the buffer will be stored
/// @param size A pointer to the size of the buffer
/// @return An int (converted from an enum) indicating the success/error value
int dynamic_buffer_pow_two(char** buffer, size_t* size) {
  if ((buffer == NULL || size == NULL) || (*buffer != NULL && size == 0) ||
      (*buffer == NULL && *size != 0)) {
    return INVALID_ARGUMENTS;
  }

  // No need to check size for 0, we checked already
  if (*buffer == NULL) {
    char* ptr = malloc(1);
    if (ptr == NULL) {
      return ALLOCATION_FAILURE;
    }
    *buffer = ptr;
    *size = 1;
    return SUCCESS;
  }

  size_t new_size = next_pow2(*size);
  if (new_size == 0) return ALLOCATION_FAILURE;
  char* ptr = realloc(*buffer, new_size);

  if (ptr == NULL) {
    char* malloc_ptr = malloc(new_size);
    if (malloc_ptr == NULL) {
      return ALLOCATION_FAILURE;
    }
    memcpy(malloc_ptr, *buffer, *size);
    free(*buffer);
    ptr = malloc_ptr;
  }

  *buffer = ptr;
  *size = new_size;

  return SUCCESS;
}

/// @brief Reads a line from file (ASCII encoding), ignoring the newline
/// character. Stores the string in the pointer pointed by target.
/// @param file The file to which the text will be read.
/// @param target A pointer to a pointer which will point to the result
/// @return Value that indicates success or an error.
int read_line_from_file(FILE* file, char** target) {
  if (file == NULL || target == NULL) {
    return INVALID_ARGUMENTS;
  }

  char* buffer = NULL;
  size_t buffer_size = 0;
  size_t buffer_used = 0;

  bool eof_reached = false;
  bool error_set = false;

  while (true) {
    char c = 0;

    // Is this inneficient?
    size_t read = fread(&c, 1, 1, file);

    if (read == 0) {
      if (feof(file)) {
        eof_reached = true;
      }
      if (ferror(file)) {
        error_set = true;
      }
      break;
    }

    if (c == '\n') {
      // Ok, we found one and we have some text, time to bail
      if (buffer_used > 0) {
        break;
      } else {
        // We ignore all the new line characters until we read something
        // that is not a newline character
        continue;
      }
    }

    if (buffer_size == buffer_used) {
      int r = dynamic_buffer_pow_two(&buffer, &buffer_size);
      if (r != SUCCESS) {
        if (buffer != NULL) free(buffer);
        return r;
      }
    }

    buffer[buffer_used] = c;
    ++buffer_used;
  }

  if (error_set) {
    if (buffer != NULL) free(buffer);
    return FILE_ERROR;
  }

  if (eof_reached && buffer_used == 0) {
    return END_OF_FILE;
  }  // else if(eof_reached && bytes_read > 0) not needed, as we have a valid
     // string still

  if (buffer_size == buffer_used) {
    int r = dynamic_buffer_pow_two(&buffer, &buffer_size);
    if (r != SUCCESS) {
      if (buffer) free(buffer);
      return r;
    }
  }

  buffer[buffer_used] = 0;

  *target = buffer;

  return SUCCESS;
}

char* read_input_from_stdin() {
  char* str = NULL;
  int r = read_line_from_file(stdin, &str);

  if (r != SUCCESS) {
    printf("Reading input from stdin failed. Exiting.");
    exit(1);
  }

  return str;
}

size_t read_size_t_stdin() {
  char* str = read_input_from_stdin();
  size_t v;
  char c;

  int r = sscanf(str, "%zu%c", &v, &c);
  while (r != 1) {
    free(str);
    printf("Please, input only positive integer numbers.\n");
    str = read_input_from_stdin();
    r = sscanf(str, "%zu%c", &v, &c);
  }

  free(str);
  return v;
}