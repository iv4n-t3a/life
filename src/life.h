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
	Life();
	Life(int w, int h);
	void resize(int w, int h);
	Cond& at(int x, int y);
	void switch_square(int x, int y);
	void next();
private:
	size_t to_i(int x, int y);
	int count_neighbours(int x, int y);
};

#endif
