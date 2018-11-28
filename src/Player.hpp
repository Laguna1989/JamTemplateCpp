#ifndef GAME_PLAYER_HPP_INCLUDEGUARD
#define GAME_PLAYER_HPP_INCLUDEGUARD

#include <iostream>

#include <SFML/Graphics.hpp>

#include "JamTemplate/Game.hpp"
#include "JamTemplate/GameState.hpp"

class Player : public JamTemplate::GameObject {
public:
	Player()
	{
		std::cout << "Player ctor" << std::endl;
		rect = sf::RectangleShape(sf::Vector2f(24, 24));
		rect.setFillColor(sf::Color::Yellow);
	}

	~Player()
	{
		std::cout << "player dtor" << std::endl;
	}

private:
	void doUpdate(float const elapsed) override
	{
		std::cout << "player update\n";
	}

	void doDraw() const override
	{
		getGame()->getRenderTarget()->draw(rect);
	}

	sf::RectangleShape rect;
};

#endif