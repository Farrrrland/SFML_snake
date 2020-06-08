#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

namespace sfSnake
{
	enum class color
	{
		//testing, using white in place of black, Yellow in place of brown
		Black, Brown, Red, Blue, Green, GEM, BOMB
	};

class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0), int i = 2);

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	color GetFruitcolor() const;

	void Setposition(sf::Vector2f position);

private:
	color Fruitcolor_;

	sf::Sprite sprite_;

	static const float Radius;
};
}

#endif