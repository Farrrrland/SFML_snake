#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "Game.h"

using namespace sfSnake;

std::pair<int, int> settings(1, 1);

MenuScreen::MenuScreen()
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString(
		"\n\n\n\n\n\n\n\n\nPress [SPACE] to play"
		"\n\nPress [ESC] to quit");

	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setColor(sf::Color::Green);
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 2);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);

	setBackground_ = setGrid_ = false;
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && setBackground_ == false)
	{
		setBackground_ = true;
		text_.setString(
		"\n\n\n\n\n\n\n\n\nSetting Background Color"
		"\n\nPress [Q] to choose white"
		"\n\nPress [W] to choose Black"
		"\n\nPress [E] to choose Brown"
		"\n\nPress [ESC] to quit");
		text_.setCharacterSize(20);
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&& setGrid_ == false)
	{
		if(setBackground_ == true)
		{
			//color_ = BackGroundColor::White;
			settings.first = 0;
			setGrid_ = true;
			text_.setString(
			"\n\n\n\n\n\n\n\n\nSetting Grid type"
			"\n\nPress [A] to choose white grid"
			"\n\nPress [S] to choose Black grid"
			"\n\nPress [D] to choose Brown grid"
			"\n\nPress [F] to delete grid"
			"\n\nPress [ESC] to quit");
			text_.setCharacterSize(20);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)&& setGrid_ == false)
	{
		if(setBackground_ == true)
		{
			//color_ = BackGroundColor::Black;
			settings.first = 1;
			setGrid_ = true;
			text_.setString(
			"\n\n\n\n\n\n\n\n\nSetting Grid type"
			"\n\nPress [A] to choose white grid"
			"\n\nPress [S] to choose Black grid"
			"\n\nPress [D] to choose Brown grid"
			"\n\nPress [F] to delete grid"
			"\n\nPress [ESC] to quit");
			text_.setCharacterSize(20);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)&& setGrid_ == false)
	{
		if(setBackground_ == true)
		{
			//color_ = BackGroundColor::Brown;
			settings.first = 2;
			setGrid_ = true;
			text_.setString(
			"\n\n\n\n\n\n\n\n\nSetting Grid type"
			"\n\nPress [A] to choose white grid"
			"\n\nPress [S] to choose Black grid"
			"\n\nPress [D] to choose Brown grid"
			"\n\nPress [F] to delete grid"
			"\n\nPress [ESC] to quit");
			text_.setCharacterSize(20);
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		//gridType_ = Grids::White;
		settings.second = 0;
		if(setGrid_ && setBackground_)
		{
			Game::Screen = std::make_shared<GameScreen>();
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//gridType_ = Grids::Black;
		settings.second = 1;
		if(setGrid_ && setBackground_)
		{
			Game::Screen = std::make_shared<GameScreen>();
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		//gridType_ = Grids::Brown;
		settings.second = 2;
		if(setGrid_ && setBackground_)
		{
			Game::Screen = std::make_shared<GameScreen>();
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		//gridType_ = Grids::None;
		settings.second = 3;
		if(setGrid_ && setBackground_)
		{
			Game::Screen = std::make_shared<GameScreen>();
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);
	window.draw(snakeText_);
}