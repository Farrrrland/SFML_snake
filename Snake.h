#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "SnakeNode.h"
#include "Fruit.h"

namespace sfSnake
{
	enum class Direction
	{
		Left, Right, Up, Down, Mouse
	};

class Snake
{
public:
	Snake();

	void handleInput(sf::RenderWindow& window);
	void update(sf::Time delta);
	void render(sf::RenderWindow& window);

	void checkFruitCollisions(std::vector<Fruit>& fruits);

	bool hitSelf() const;
	bool eatBomb() const;

	unsigned getSize() const;

private:
	void move();
	void grow(const color Fruitcolor);
	void checkEdgeCollisions();
	void checkSelfCollisions();
	void initNodes();
	void checkEatBomb();

	bool hitSelf_;
	bool eatBomb_;

	sf::Vector2f position_;
	sf::Vector2f MoveDir_;

	Direction direction_;

	sf::SoundBuffer pickupBuffer_;
	sf::Sound pickupSound_;

	sf::SoundBuffer dieBuffer_;
	sf::Sound dieSound_;

	std::vector<SnakeNode> nodes_;

	static const int InitialSize;
};
}

#endif