#include <iostream>
#include <array>
#include <string>

#include "life.h"
#include "config.h"


Config generate_default_config() {
	Config c;

	c.square_size = 20;
	c.field_h = 60;
	c.field_w = 110;

	c.win_name = "Game Of Life";

	c.square_color[ALIVE] = {0, 174, 0};
	c.square_color[DEAD] = {50, 50, 50};
	c.bg_color = c.square_color[DEAD];

	return c;
}
Config generate_config(int argc, char *argv[]) {
	Config c = generate_default_config();
	int i = 1;

	for (; i < argc; i++) {
		std::string arg = argv[i];
		if (arg == "-s" or arg == "--square-size")
			c.square_size = atoi(argv[++i]);
		else if (arg == "-w" or arg == "--field-wight")
			c.field_w = atoi(argv[++i]);
		else if (arg == "-h" or arg == "--field-height")
			c.field_h = atoi(argv[++i]);
		else if (arg == "-?" or arg == "--help")
			throw HELPEXEPT;
		else
			throw FORMATERR;
	}

	return c;
}
