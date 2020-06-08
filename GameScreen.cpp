#include <SFML/Graphics.hpp>
#include <iostream>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "Game.h"

using namespace sfSnake;
extern std::pair<int, int> settings;

sf::Texture Background;
sf::Texture Grid;

GameScreen::GameScreen() : snake_()
{
	sf::Vector2f SettingPos;
	SettingPos.x = SettingPos.y = 0;
	BackgroundSprite_.setPosition(SettingPos);
	GridSprite_.setPosition(SettingPos);
	switch (settings.first)
	{
		case 0: BackgroundColor_ = BackGroundColor::White; 
				std::cout << "Backgrouns-White" << std::endl;
				Background.loadFromFile("Textures/WhiteBackground.png");
				break;
		case 1: BackgroundColor_ = BackGroundColor::Black; 
				std::cout << "Backgrouns-Black" << std::endl;
				Background.loadFromFile("Textures/BlackBackground.png");
				break;
		case 2: BackgroundColor_ = BackGroundColor::Brown; 
				std::cout << "Backgrouns-Brown" << std::endl;
				Background.loadFromFile("Textures/BrownBackground.png");
				break;
		default: BackgroundColor_ = BackGroundColor::Black; 
				std::cout << "Backgrouns-Black" << std::endl;
				Background.loadFromFile("Textures/BlackBackground.png");
				break;
	}
	switch (settings.second)
	{
		case 0: Grids_ = Grids::White; 
				std::cout << "Grids-White" << std::endl;
				Grid.loadFromFile("Textures/WhiteGrid.png");
				break;
		case 1: Grids_ = Grids::Black; 
				std::cout << "Grids-Black" << std::endl;
				Grid.loadFromFile("Textures/BlackGrid.png");
				break;
		case 2: Grids_ = Grids::Brown; 
				std::cout << "Grids-Brown" << std::endl;
				Grid.loadFromFile("Textures/BrownGrid.png");
				break;
		case 3: Grids_ = Grids::None; 
				std::cout << "Grids-None" << std::endl;
				break;
		default: Grids_ = Grids::None; 
				std::cout << "Grids-None" << std::endl;
				break;
	}
	BackgroundSprite_.setTexture(Background);
	if(Grids_ != Grids::None)
	{
		GridSprite_.setTexture(Grid);
	}
	
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if(fruit_.size() == 0)
	{
		InitializeFruit();
	}
	else if (fruit_.size() == 14)
	{
		bool Nutritious = true;
		int cntInnutritious = 0;
		for (auto it = fruit_.begin(); it != fruit_.end(); ++it)
		{
			if(it->GetFruitcolor() == color::GEM || it->GetFruitcolor() == color::BOMB) continue;
			switch (it->GetFruitcolor())
			{
				case color::Black: ++cntInnutritious; break;
				case color::Brown: ++cntInnutritious; break;
				default: break;
			}
			if (cntInnutritious == 3)
			{
				generateFruit(Nutritious);
				break;
			}
		}
		if (cntInnutritious == 2)
		{
			Nutritious = false;
			generateFruit(Nutritious);
		}
	}

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf() || snake_.eatBomb())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	window.draw(BackgroundSprite_);
	if(Grids_ != Grids::None)
	{
		window.draw(GridSprite_);
	}
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::InitializeFruit()
{
	generateBonus(true);
	generateBonus(true);
	generateBonus(false);
	bool Nutritious = false;
	for(int i=0; i<12; i++)
	{
		if(i == 3) 
		{
			Nutritious = true;
		}
		generateFruit(Nutritious);
	}
}

void GameScreen::generateBonus(bool IsBomb)
{
	static std::default_random_engine engine(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Unit);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Unit);

	int GEMorBOMB = 5;
	if(IsBomb) GEMorBOMB = 6;
	Fruit Bonuspoint(sf::Vector2f(xDistribution(engine), yDistribution(engine)), GEMorBOMB);

	if(fruit_.size() != 0)
	{
		auto it = fruit_.begin(); 
		while(it != fruit_.end())
		{
			if (it->getBounds().intersects(Bonuspoint.getBounds()))
			{
				Bonuspoint.Setposition(sf::Vector2f(xDistribution(engine), yDistribution(engine)));
				it = fruit_.begin();
			}
			else
			{
				++it;
			}
		}
	}
	fruit_.push_back(Bonuspoint);
}

void GameScreen::generateFruit(bool Nutritious)
{
	static std::default_random_engine engine(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width - SnakeNode::Unit);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Unit);

	int minColor = 0, maxColor = 4;
	if(Nutritious == false)
	{
		maxColor = 1;
	}
	else
	{
		minColor = 2;
	}

	std::uniform_int_distribution<int> colorDistribution(minColor, maxColor);
	
	Fruit Fruitpoint(sf::Vector2f(xDistribution(engine), yDistribution(engine)), colorDistribution(engine));

	if(fruit_.size() != 0)
	{
		auto it = fruit_.begin(); 
		while(it != fruit_.end())
		{
			if (it->getBounds().intersects(Fruitpoint.getBounds()))
			{
				Fruitpoint.Setposition(sf::Vector2f(xDistribution(engine), yDistribution(engine)));
				it = fruit_.begin();
			}
			else
			{
				++it;
			}
		}
	}
	fruit_.push_back(Fruitpoint);
}	
