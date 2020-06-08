#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Unit = 10.f;

sf::Texture HeadtextureA;
sf::Texture HeadtextureB;
sf::Texture BodytextureA;
sf::Texture BodytextureB;


SnakeNode::SnakeNode(sf::Vector2f position, float radian, bool isHead)
: position_(position)
{
	BodyNode_.first.setPosition(position_);
	BodyNode_.second.setPosition(position_);
	radian0_ = radian;

	if(isHead)
	{
		HeadtextureA.loadFromFile("Textures/HeadWings.png");
		HeadtextureB.loadFromFile("Textures/HeadBase.png");		
		BodyNode_.first.setTexture(HeadtextureA);		
		BodyNode_.second.setTexture(HeadtextureB);
		BodyNode_.first.setOrigin(15, 10.5);
		BodyNode_.second.setOrigin(3, 3);
	}
	else
	{
		BodytextureA.loadFromFile("Textures/BodyTex.png");	
		BodytextureB.loadFromFile("Textures/BodyBase.png");	
		BodyNode_.first.setTexture(BodytextureA);
		BodyNode_.second.setTexture(BodytextureB);
		BodyNode_.first.setOrigin(7.5, 2);
		BodyNode_.second.setOrigin(7.5, 7.5);
	}
}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	BodyNode_.first.setPosition(position_);
	BodyNode_.second.setPosition(position_);
}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	BodyNode_.first.setPosition(position_);
	BodyNode_.second.setPosition(position_);
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	BodyNode_.first.setPosition(position_);
	BodyNode_.second.setPosition(position_);
}

sf::FloatRect SnakeNode::getBounds() const
{
	return BodyNode_.second.getGlobalBounds();
}

sf::FloatRect SnakeNode::getInnerBounds() const
{
	return BodyNode_.first.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(BodyNode_.second);
	window.draw(BodyNode_.first);
}

void SnakeNode::rotate(float radian)
{
	BodyNode_.first.rotate(radian);
}

float SnakeNode::getRadian() const
{
	return radian0_;
}

void SnakeNode::setRadian(float radian)
{
	radian0_ = radian;
}