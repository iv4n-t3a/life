#ifndef LIFE
#define LIFE

#include <vector>
#include <iostream>


typedef size_t Square;
enum Cond {
	DEAD,
	ALIVE
};

class Life {
	std::vector<Cond> field;
	int w, h;
public:
	Life(int w, int h);
	void next();

	Cond& at(int x, int y);
	void switch_square(int x, int y);
	int get_w();
	int get_h();
private:
	size_t to_i(int x, int y);
	int count_neighbours(int x, int y);
};

#endif
