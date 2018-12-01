#ifndef GAME_PLAYER_HPP_INCLUDEGUARD
#define GAME_PLAYER_HPP_INCLUDEGUARD

#include <iostream>

#include <SFML/Graphics.hpp>

#include "JamTemplate/Game.hpp"
#include "JamTemplate/Transform.hpp"

#include "GameProperties.hpp"
class StateGame;

class Player : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Player(StateGame& sg) : m_gameState(sg)
	{
		std::cout << "Player ctor" << std::endl;
		m_rect = sf::RectangleShape(sf::Vector2f(24, 24));
		m_rect.setFillColor(sf::Color::Yellow);
		setPosition(sf::Vector2f{ 10, 20 });

		
	}

	~Player()
	{
		std::cout << "player dtor" << std::endl;
	}



private:

	float m_shootTimer = 0.0f;

	void doUpdate(float const elapsed) override
	{
		updateShooting(elapsed);
		updateMovement(elapsed);
	}

	void updateShooting(float elapsed)
	{
		m_shootTimer -= elapsed;
		if (m_shootTimer > 0) return;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			shoorArrow();
		}
	}
	void updateMovement(float elapsed)
	{
		setVelocity({ 0.f,0.f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			setVelocity({0,-GP::playerMovementSpeed()});
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		{
			setVelocity({ 0,GP::playerMovementSpeed()  });
		}
		updateTransform(elapsed);
		m_rect.setPosition(getPosition());
	}

	void Player::doDraw() const override
	{
		getGame()->getRenderTarget()->draw(m_rect);
	}

	void doCreate()
	{
		float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
		float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
		setBounds(sf::FloatRect(0, 0, w, h));
	}
	void shoorArrow();

	StateGame& m_gameState;

	sf::RectangleShape m_rect;
};

#endif
