#include <SFML/Graphics.hpp>
#include <iostream>

#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 5.f;

sf::Texture BlackFruit;
sf::Texture BrownFruit;
sf::Texture RedFruit;
sf::Texture BlueFruit;
sf::Texture GreenFruit;
sf::Texture GEM;
sf::Texture BOMB;

Fruit::Fruit(sf::Vector2f position, int i)
{
	BlackFruit.loadFromFile("Textures/BlackFruit.png");
	BrownFruit.loadFromFile("Textures/BrownFruit.png");
	RedFruit.loadFromFile("Textures/RedFruit.png");
	BlueFruit.loadFromFile("Textures/BlueFruit.png");
	GreenFruit.loadFromFile("Textures/GreenFruit.png");
	GEM.loadFromFile("Textures/GEM.png");
	BOMB.loadFromFile("Textures/BOMB.png");

	sprite_.setPosition(position);
	switch (i)
	{
		case 0: sprite_.setTexture(BlackFruit);
				Fruitcolor_ = color::Black;
				break;
		case 1: sprite_.setTexture(BrownFruit);
				Fruitcolor_ = color::Brown;
				break;
		case 2: sprite_.setTexture(RedFruit);
				Fruitcolor_ = color::Red;
				break;
		case 3: sprite_.setTexture(BlueFruit);
				Fruitcolor_ = color::Blue;
				break;
		case 4: sprite_.setTexture(GreenFruit);
				Fruitcolor_ = color::Green;
				break;
		case 5: sprite_.setTexture(GEM);
				Fruitcolor_ = color::GEM;
				break;
		case 6: sprite_.setTexture(BOMB);
				Fruitcolor_ = color::BOMB;
				break;
		default: sprite_.setTexture(RedFruit);
				 Fruitcolor_ = color::Red;
				 break;
	}
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}

sf::FloatRect Fruit::getBounds() const
{
	return sprite_.getGlobalBounds();
}

color Fruit::GetFruitcolor() const
{
	return Fruitcolor_;
}

void Fruit::Setposition(sf::Vector2f position)
{
	sprite_.setPosition(position);
}