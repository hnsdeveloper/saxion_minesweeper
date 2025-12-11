#include <stdio.h>
#include "board.h"

int main() {
	Board* b = create_board(10, 10);
	draw_board(b);

	return 0;
}
