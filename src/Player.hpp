#ifndef GAME_PLAYER_HPP_INCLUDEGUARD
#define GAME_PLAYER_HPP_INCLUDEGUARD

#include <iostream>

#include <SFML/Graphics.hpp>

#include "JamTemplate/Game.hpp"
#include "JamTemplate/Transform.hpp"

class StateGame;

class Player : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Player(StateGame& sg) : m_gameState(sg)
	{
		std::cout << "Player ctor" << std::endl;
		rect = sf::RectangleShape(sf::Vector2f(24, 24));
		rect.setFillColor(sf::Color::Yellow);
		setPosition(sf::Vector2f{ 10, 20 });
	}

	~Player()
	{
		std::cout << "player dtor" << std::endl;
	}



private:
	void doUpdate(float const elapsed) override
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			shoorArrow();
		}
	}

	void doDraw() const override;

	void shoorArrow();

	StateGame& m_gameState;

	sf::RectangleShape rect;
};

#endif