#include <iostream>
#include <string.h>

#include "config.h"
#include "ui.h"


void help_and_exit() {
	std::cout << "Game of Life, usage:" << std::endl <<
		"life [options]" << std::endl << std::endl <<
		"Options:" << std::endl <<
		"	-s or --square_size set displayed square size in pixels" << std::endl <<
		"	-w or --field-wight set field wight in squares" << std::endl <<
		"	-h or --field-height set field height in squares" << std::endl <<
		"	-? or --help show this message" << std::endl << std::endl <<
		"use space to switch run/setup mode and up/down/left/right keys and mouse wheel for navigation" << std::endl;
	std::exit(0);
}

int main(int argc, char *argv[]) {
	Config cfg;
	try {
		cfg = generate_config(argc, argv);
	} catch (ParsingException) {
		help_and_exit();
	}
	sf::RenderWindow win(sf::VideoMode(cfg.square_size * cfg.field_w, cfg.square_size * cfg.field_h), cfg.win_name);
	Life l(cfg.field_w, cfg.field_h);
	UI ui(win, l, cfg);
	ui.run();
	return 0;
}
