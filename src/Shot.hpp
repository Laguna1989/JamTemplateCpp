#ifndef GAME_SHOT_HPP_INCLUDEGUARD
#define GAME_SHOT_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include "JamTemplate/GameObject.hpp"
#include "JamTemplate/Transform.hpp"

class Shot : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	Shot(sf::Vector2f p)
	{
		setPosition(p);
		setVelocity(sf::Vector2f{ GP::shotMovementSpeed(),0 });
		m_rect = sf::RectangleShape(sf::Vector2f(24, 4));
		m_rect.setFillColor(sf::Color::Blue);
	}

	~Shot() = default;

	const sf::Shape& getShape() const { return m_rect; }
private:
	void doUpdate(float const elapsed) override
	{
		updateTransform(elapsed);
		m_rect.setPosition(getPosition());
		if (getPosition().x > getGame()->getRenderTarget()->getSize().x + 50) 
		{
			kill();
		}
	}

	void doDraw() const override
	{
		getGame()->getRenderTarget()->draw(m_rect);
	}


	sf::RectangleShape m_rect;
};

using ShotPtr = std::shared_ptr<Shot>;

#endif
