#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "ui.h"



UI::UI(sf::RenderWindow& _w, Config c) : window(_w), cfg(c) {
	sf::Vector2u size = window.getSize();
	w = size.x / cfg.square_size;
	h = size.y / cfg.square_size;
	life = Life(w, h);
	redraw();
}

void UI::setup() {
	sf::Event event;
	while (window.isOpen()) {
		redraw();
		window.waitEvent(event);

		if (event.type == sf::Event::MouseButtonPressed) {
			int x = event.mouseButton.x / cfg.square_size,
				y = event.mouseButton.y / cfg.square_size;
			life.switch_square(x, y);
		} else if (event.type == sf::Event::KeyPressed) {
			return;
		} else if (event.type == sf::Event::Closed) {
			exit(0);
		}
	}
}
void UI::run() {
	sf::Event event;
	while (window.isOpen()) {
		life.next();
		redraw();

		if (not window.pollEvent(event))
			continue;

		if (event.type == sf::Event::MouseButtonPressed) {
			int x = event.mouseButton.x / cfg.square_size,
				y = event.mouseButton.y / cfg.square_size;
			life.switch_square(x, y);
			setup();
		} else if (event.type == sf::Event::KeyPressed) {
			setup();
		} else if (event.type == sf::Event::Closed) {
			exit(0);
		}
	}
}
void UI::redraw() {
	window.clear( to_sf_color(cfg.bg_color) );

	for (int x = 0; x < w; x++)
		for (int y = 0; y < h; y++)
		{
			sf::RectangleShape shape(sf::Vector2f(cfg.square_size, cfg.square_size));
			shape.setPosition(x * cfg.square_size, y * cfg.square_size);
			shape.setFillColor( to_sf_color(cfg.square_color[life.at(x, y)]) );
			window.draw(shape);
		}

	window.display();
}

sf::Color UI::to_sf_color(Color c) {
	return sf::Color(c.r, c.g, c.b);
}
