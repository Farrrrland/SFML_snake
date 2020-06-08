#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
	enum class BackGroundColor
	{
		White, Black, Brown
	};
	enum class Grids
	{
		White, Black, Brown, None
	};
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void generateFruit(bool Nutritious);
	void generateBonus(bool IsBomb);
	void InitializeFruit();


private:
	Snake snake_;
	std::vector<Fruit> fruit_;
	BackGroundColor BackgroundColor_;
	Grids Grids_;
	sf::Sprite BackgroundSprite_;
	sf::Sprite GridSprite_;
};
}

#endif