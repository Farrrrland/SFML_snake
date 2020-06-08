#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>
#include <cmath>
#include <random>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false), MoveDir_(sf::Vector2f(0, -SnakeNode::Unit))
{
	initNodes();

	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);

	eatBomb_ = false;
	hitSelf_ = false;
}

void Snake::initNodes()
{
	float InitRadian = std::atan2(MoveDir_.y, MoveDir_.x) / acos(-1) * 180;
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		if(i == 0)
		{
			bool Head = true;
			nodes_.push_back(SnakeNode(sf::Vector2f(
				Game::Width / 2 - SnakeNode::Unit / 2,
				Game::Height / 2 - (SnakeNode::Unit / 2) + (SnakeNode::Unit * i)), InitRadian, Head));
		}
		else
		{
			nodes_.push_back(SnakeNode(sf::Vector2f(
				Game::Width / 2 - SnakeNode::Unit / 2,
				Game::Height / 2 - (SnakeNode::Unit / 2) + (SnakeNode::Unit * i)), InitRadian));
			nodes_[i].setRadian(nodes_[i-1].getRadian());
		}
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		direction_ = Direction::Up;
		MoveDir_ = sf::Vector2f(0, -SnakeNode::Unit);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		direction_ = Direction::Down;
		MoveDir_ = sf::Vector2f(0, SnakeNode::Unit);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		direction_ = Direction::Left;
		MoveDir_ = sf::Vector2f(-SnakeNode::Unit, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		direction_ = Direction::Right;
		MoveDir_ = sf::Vector2f(SnakeNode::Unit, 0);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
		if((sf::Mouse::getPosition(window).y-nodes_[0].getPosition().y) / (sf::Mouse::getPosition(window).x-nodes_[0].getPosition().x)<=1
			&& (sf::Mouse::getPosition(window).y-nodes_[0].getPosition().y) / (sf::Mouse::getPosition(window).x-nodes_[0].getPosition().x)>=-1)
		{
			if(sf::Mouse::getPosition(window).x-nodes_[0].getPosition().x > 0)
				MoveDir_ = sf::Vector2f(10, 10 * (sf::Mouse::getPosition(window).y-nodes_[0].getPosition().y) / (sf::Mouse::getPosition(window).x-nodes_[0].getPosition().x));
			else
				MoveDir_ = sf::Vector2f(-10, -10 * (sf::Mouse::getPosition(window).y-nodes_[0].getPosition().y) / (sf::Mouse::getPosition(window).x-nodes_[0].getPosition().x));
		}
		else
		{
			if(sf::Mouse::getPosition(window).y-nodes_[0].getPosition().y > 0)
				MoveDir_ = sf::Vector2f(10 * (sf::Mouse::getPosition(window).x-nodes_[0].getPosition().x) / (sf::Mouse::getPosition(window).y-nodes_[0].getPosition().y), 10);
			else
				MoveDir_ = sf::Vector2f(-10 * (sf::Mouse::getPosition(window).x-nodes_[0].getPosition().x) / (sf::Mouse::getPosition(window).y-nodes_[0].getPosition().y), -10);
		 
		}
		direction_ = Direction::Mouse;
	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEatBomb();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	static std::default_random_engine engine(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Unit);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Unit);
	decltype(fruits.begin()) toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getInnerBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		const color Fruitcolor = toRemove->GetFruitcolor();
		if(Fruitcolor == color::BOMB)
		{
			eatBomb_ = true;
		}
		else if(Fruitcolor == color::GEM)
		{
			grow(Fruitcolor);
		}
		else
		{
			grow(Fruitcolor);
			fruits.erase(toRemove);
		}
		auto bonus_it = fruits.begin();
		while((bonus_it->GetFruitcolor() == color::GEM || bonus_it->GetFruitcolor() == color::BOMB) && !eatBomb_)
		{

			bonus_it->Setposition(sf::Vector2f(xDistribution(engine), yDistribution(engine)));
			
			auto check_it = fruits.begin(); 
			while(check_it != fruits.end())
			{
				if (check_it != bonus_it && check_it->getBounds().intersects(bonus_it->getBounds()))
				{
					bonus_it->Setposition(sf::Vector2f(xDistribution(engine), yDistribution(engine)));
					check_it = fruits.begin();
				}
				else
				{
					++check_it;
				}
			}
			bonus_it ++;
		}
	}
}

void Snake::grow(const color Fruitcolor)
{
	switch(Fruitcolor)
	{
		case color::Red: for(int loop = 0; loop < 3; loop++)
				  {
						nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	 					nodes_[nodes_.size() - 1].getPosition().y), nodes_[nodes_.size() - 1].getRadian()));
						nodes_[nodes_.size() - 1].rotate(nodes_[nodes_.size() - 1].getRadian() + 90);
				  }
				  break;
		case color::Blue: for(int loop = 0; loop < 2; loop++)
				   {
						nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	 					nodes_[nodes_.size() - 1].getPosition().y), nodes_[nodes_.size() - 1].getRadian()));
						nodes_[nodes_.size() - 1].rotate(nodes_[nodes_.size() - 1].getRadian() + 90);
				   }
				  break;
		case color::Green: nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	 				nodes_[nodes_.size() - 1].getPosition().y), nodes_[nodes_.size() - 1].getRadian()));
					nodes_[nodes_.size() - 1].rotate(nodes_[nodes_.size() - 1].getRadian() + 90);
					break;
		case color::GEM: 
				   	for(int loop = 0; loop < 15; loop++)
				   	{
						nodes_.push_back(SnakeNode(sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
	 					nodes_[nodes_.size() - 1].getPosition().y), nodes_[nodes_.size() - 1].getRadian()));
						nodes_[nodes_.size() - 1].rotate(nodes_[nodes_.size() - 1].getRadian() + 90);
				   	}
				   break;
		default : break;
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

bool Snake::eatBomb() const
{
	return eatBomb_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 1; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getInnerBounds()))
		{
			std::cout << i << std::endl;
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];
	if (headNode.getPosition().x <= 0 || headNode.getPosition().x >= Game::Width || headNode.getPosition().y <= 0 || headNode.getPosition().y >= Game::Height)
	{
		std::cout << headNode.getPosition().x << ", " << headNode.getPosition().y << std::endl;
		dieSound_.play();
		sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
		hitSelf_ = true;
	}
}

void Snake::checkEatBomb()
{
	if(eatBomb())
	{
		std::cout <<  "Boom!\n " << std::endl;
		dieSound_.play();
		sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
	}
}

void Snake::move()
{
	//旋转只需要转.first，也就是texture部分，背景部分作为中心对称图形不需要参与旋转
	
	float radian = std::atan2(MoveDir_.y, MoveDir_.x) / acos(-1) * 180;
	if(nodes_[0].getRadian() != radian)
	{
		//Rotate Head
		nodes_[0].rotate(radian - nodes_[0].getRadian());
		nodes_[0].setRadian(radian);
	}
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
		
		if(nodes_[i].getRadian() != nodes_[i-1].getRadian())
		{
			//Rotate Body
			nodes_[i].rotate(nodes_[i-1].getRadian() - nodes_[i].getRadian());
			nodes_[i].setRadian(nodes_[i-1].getRadian());
		}
	}

	nodes_[0].move(MoveDir_.x, MoveDir_.y);
	
}

void Snake::render(sf::RenderWindow& window)
{
	for (auto node : nodes_)
		node.render(window);
}