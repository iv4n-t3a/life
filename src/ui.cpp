#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <assert.h>

#include "config.h"
#include "ui.h"



UI::UI(sf::RenderWindow& w, Life l, Config c) : window(w), life(l), cfg(c) {
	sf::Vector2u size = window.getSize();
	square_size = cfg.square_size;
	win_w = size.x / square_size;
	win_h = size.y / square_size;
	win_x = 0;
	win_y = 0;
	redraw();
}

void UI::setup() {
	sf::Event event;
	while (window.isOpen()) {
		redraw();
		window.waitEvent(event);

		if (event.type == sf::Event::MouseButtonPressed) {
			switch_clicked(event);
		} else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Space) {
			return;
		} else if (event.type == sf::Event::KeyPressed) {
			move_window(event);
		} else if (event.type == sf::Event::MouseWheelScrolled) {
			update_scale(event);
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
			switch_clicked(event);
			setup();
		} else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Space) {
			setup();
		} else if (event.type == sf::Event::KeyPressed) {
			move_window(event);
		} else if (event.type == sf::Event::MouseWheelScrolled) {
			update_scale(event);
		} else if (event.type == sf::Event::Closed) {
			exit(0);
		}
	}
}
void UI::switch_clicked(sf::Event mouseclick) {
	assert(mouseclick.type == sf::Event::MouseButtonPressed or mouseclick.type == sf::Event::MouseButtonReleased);
	int x = (mouseclick.mouseButton.x / square_size + win_x) % life.get_w(),
		y = (mouseclick.mouseButton.y / square_size + win_y) % life.get_h();
	life.switch_square(x, y);
}
void UI::move_window(sf::Event keypress) {
	assert(keypress.type == sf::Event::KeyPressed or keypress.type == sf::Event::KeyReleased);
	switch (keypress.key.code) {
		case sf::Keyboard::Up: win_y = (win_y + life.get_h() - 1) % life.get_h(); break;
		case sf::Keyboard::Left: win_x = (win_x + life.get_w() - 1) % life.get_w(); break;
		case sf::Keyboard::Down: win_y = (win_y + 1) % life.get_h(); break;
		case sf::Keyboard::Right: win_x = (win_x + 1) % life.get_w(); break;
		default: break;
	}
}
void UI::update_scale(sf::Event wheelscroll) {
	assert(wheelscroll.type == sf::Event::MouseWheelScrolled);

	sf::Vector2u size = window.getSize();
	int
		delta = wheelscroll.mouseWheelScroll.delta,
		new_square_size = square_size + delta,
		new_win_w = size.x / new_square_size,
		new_win_h = size.y / new_square_size;

	if (
			new_square_size <= 2 or new_square_size >= 60 or (
				new_win_w > life.get_w() and new_win_h > life.get_h() and
				new_square_size < square_size and new_square_size < cfg.square_size
			)
	) return;

	square_size = new_square_size;
	win_x = std::max(win_x - new_win_w + win_w, 0);
	win_y = std::max(win_y - new_win_h + win_h, 0);
	win_w = new_win_w;
	win_h = new_win_h;
}
void UI::redraw() {
	window.clear( to_sf_color(cfg.bg_color) );
	for (int x = 0; x < win_w; x++) {
		for (int y = 0; y < win_h; y++)
		{
			Cond c = life.at(x + win_x, y + win_y);
			sf::RectangleShape shape(sf::Vector2f(square_size, square_size));
			shape.setPosition(x * square_size, y * square_size);
			shape.setFillColor( to_sf_color(cfg.square_color[c]) );
			window.draw(shape);
		}
	}
	window.display();
}

sf::Color UI::to_sf_color(Color c) {
	return sf::Color(c.r, c.g, c.b);
}
