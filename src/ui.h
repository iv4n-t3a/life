#ifndef UI_H
#define UI_H

#include <array>
#include <string>
#include <tuple>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "life.h"


class UI {
	Life life;
	sf::RenderWindow& window;
	Config cfg;
	int w, h;
public:
	UI(sf::RenderWindow&, Config c);
	void setup();
	void run();
private:
	void redraw();
	sf::Color to_sf_color(Color);
};


#endif // #ifndef UI_H
