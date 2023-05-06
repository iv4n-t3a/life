#include "life.h"

#include <assert.h>


Life::Life(int _w, int _h) {
	w = _w;
	h = _h;
	field = std::vector<Cond>(w * h, DEAD);
}

void Life::next() {
	std::vector<Cond> new_field = field;
	for (int x = 0; x < w; x++) {
		for (int y = 0; y < h; y++) {
			int c = count_neighbours(x, y);
			if ((c != 2 and c != 3) and at(x, y) == ALIVE)
				new_field[to_i(x, y)] = DEAD;
			if (c == 3 and at(x, y) == DEAD)
				new_field[to_i(x, y)] = ALIVE;
		}
	}
	field = new_field;
}
int Life::count_neighbours(int x, int y) {
	int c = 0;
	for (int x_offset : {-1, 0, 1}) {
		for (int y_offset : {-1, 0, 1}) {
			int new_x, new_y;
			new_x = x + x_offset;
			new_y = y + y_offset;
			Cond cond = at(new_x, new_y);
			c += cond == ALIVE;
		}
	}
	c -= at(x, y) == ALIVE;
	return c;
}

Cond& Life::at(int x, int y) {
	return field[to_i(x, y)];
}
void Life::switch_square(int x, int y) {
	field[to_i(x, y)] = field[to_i(x, y)] == ALIVE ? DEAD : ALIVE;
}
size_t Life::to_i(int x, int y) {
	return (x % w) * h + y % h;
}
int Life::get_w() {
	return w;
}
int Life::get_h() {
	return h;
}
