#ifndef CONFIG
#define CONFIG

#include <iostream>
#include <array>

#include "life.h"


enum ParsingException {
    FORMATERR,
	HELPEXEPT,
};
struct Color {
	uint8_t r, g, b;
};

struct Config {
    int square_size;
	std::string etcdir;

	Color bg_color;
	std::array<Color, 2> square_color;
};

Config generate_config(int argc, char *argv[]);

#endif
