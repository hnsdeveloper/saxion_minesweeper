CC := gcc
CFLAGS := -Wall -Wextra -O2
TARGET := minesweeper

ifdef DEBUG
	CFLAGS += -DMINESWEEPER_DEBUG=1
endif

SRC := $(shell find . -name "*.c" -type f)
OBJ := $(SRC:.c=.o)

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean : 
	rm -f $(OBJ) $(TARGET)

.PHONY : clean