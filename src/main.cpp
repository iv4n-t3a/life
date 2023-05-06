#include "config.h"
#include "ui.h"


int main(int argc, char *argv[]) {
	Config cfg = generate_config(argc, argv);
	sf::RenderWindow win(sf::VideoMode(600, 800), "Game Of Life");
	UI ui(win, cfg);
	ui.run();
	return 0;
}
