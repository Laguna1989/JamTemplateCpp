#ifndef GAME_PLAYER_HPP_INCLUDEGUARD
#define GAME_PLAYER_HPP_INCLUDEGUARD

#include <iostream>

#include <SFML/Graphics.hpp>

#include "JamTemplate/Game.hpp"
#include "JamTemplate/Transform.hpp"
#include "JamTemplate/SmartSprite.hpp"

#include "GameProperties.hpp"
class StateGame;

class Player : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Player(StateGame& sg) : m_gameState(sg)
	{
		setPosition(sf::Vector2f{ 10, 20 });
	}

	~Player() = default;


private:

	float m_shootTimer = 0.0f;

	void doUpdate(float const elapsed) override
	{
		updateShooting(elapsed);
		updateMovement(elapsed);
		m_sprite.update(elapsed);
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
		m_sprite.setPosition(getPosition());
	}

	void doDraw() const override
	{
		m_sprite.draw(getGame()->getRenderTarget());
	}

	void doCreate()
	{
		float w = static_cast<float>(getGame()->getRenderTarget()->getSize().x);
		float h = static_cast<float>(getGame()->getRenderTarget()->getSize().y);
		setBoundsPosition(sf::FloatRect(0, 0, w, h-24));

		m_sprite.loadSprite("assets/player.png");
	}
	void shoorArrow();

	StateGame& m_gameState;

	JamTemplate::SmartSprite m_sprite;
};

#endif
