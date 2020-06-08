#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Screen.h"


extern std::pair<int, int> settings;

namespace sfSnake
{
class MenuScreen : public Screen
{
public:
	MenuScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Font font_;
	sf::Text snakeText_;
	sf::Text text_;
	bool setBackground_;
	bool setGrid_;
};
}

#endif