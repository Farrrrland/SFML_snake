#ifndef SNAKE_NODE_H
#define SNAKE_NODE_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace sfSnake
{
class SnakeNode
{
public:
	SnakeNode(sf::Vector2f position = sf::Vector2f(0, 0), float radian = -90, bool isHead = false);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);

	void move(float xOffset, float yOffset);
	void rotate(float radian);
	void render(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	sf::FloatRect getBounds() const;
	sf::FloatRect getInnerBounds() const;

	float getRadian() const;
	void setRadian(float radian);

	static const float Unit;

private:
	std::pair<sf::Sprite, sf::Sprite> BodyNode_;
	sf::Vector2f position_;
	float radian0_;
	bool isHead;
};
}

#endif