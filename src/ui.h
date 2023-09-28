#ifndef UI_H
#define UI_H

#include <array>
#include <string>
#include <tuple>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "config.h"
#include "life.h"


class UIState;

class UI {
	friend UIState;

	Life life;
	sf::RenderWindow& window;
	int win_w, win_h, win_x, win_y, square_size;
	Config cfg;
	UIState* state;
public:
	UI(sf::RenderWindow&, Life, Config);
	void run();
private:
	void process_click(sf::Event click);
	void move_window(sf::Event keypress);
	void update_scale(sf::Event wheelscroll);
	void redraw();

	void switch_state(UIState* next);
	sf::Color to_sf_color(Color);
};

class UIState {
public:
	virtual void update_life(Life&) = 0;
	virtual void process_click(UI*, Life&, int x, int y) = 0;
	virtual void process_space_pressed(UI*) = 0;
protected:
	void switch_state(UI*, UIState* next);
};

#endif // #ifndef UI_H
