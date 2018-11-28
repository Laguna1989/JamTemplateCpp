#ifndef GAME_BALLOON_HPP_INCLUDEGUARD
#define GAME_BALLOON_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Game.hpp"

class Balloon : public JamTemplate::GameObject {
public:
	Balloon()
	{
		std::cout << "Balloon ctor" << std::endl;
		circ = sf::CircleShape(12);
		circ.setFillColor(sf::Color::Red);
		circ.setPosition(40, 40);
	}

	~Balloon()
	{
		std::cout << "Balloon dtor" << std::endl;
	}

private:
	void doUpdate(float const elapsed) override
	{
		std::cout << "Balloon update\n";
	}

	void doDraw() const override
	{
		getGame()->getRenderTarget()->draw(circ);
	}

	sf::CircleShape circ;
};

using BalloonPtr = std::shared_ptr<Balloon>;

#endif