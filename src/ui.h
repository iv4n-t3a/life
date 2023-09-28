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
	int win_w, win_h, win_x, win_y, square_size;
	Config cfg;
public:
	UI(sf::RenderWindow&, Life, Config);
	void setup();
	void run();
private:
	void switch_clicked(sf::Event mouseclick);
	void move_window(sf::Event keypress);
	void update_scale(sf::Event wheelscroll);
	void redraw();
	sf::Color to_sf_color(Color);
};


#endif // #ifndef UI_H
