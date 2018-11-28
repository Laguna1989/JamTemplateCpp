#ifndef GAME_PLAYER_HPP_INCLUDEGUARD
#define GAME_PLAYER_HPP_INCLUDEGUARD

#include <iostream>

#include <SFML/Graphics.hpp>

#include "JamTemplate/GameState.hpp"

class Player : public JamTemplate::GameObject {
public:
	Player()
	{
		std::cout << "Player ctor" << std::endl;
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

	void doDraw(sf::RenderTarget& rt) const override
	{

	}

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif