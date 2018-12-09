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
		
		
		m_rect = std::make_shared<JamTemplate::SmartShape>();
		m_rect->makeRect(sf::Vector2f{ 24, 4 });
		m_rect->setColor(sf::Color::Blue);
	}

	~Shot() = default;

	const JamTemplate::SmartShape::Sptr getShape() const { return m_rect; }
private:
	void doUpdate(float const elapsed) override
	{
		updateTransform(elapsed);
		m_rect->setPosition(getPosition());
		if (getPosition().x > getGame()->getRenderTarget()->getSize().x + 50) 
		{
			kill();
		}
	}

	void doDraw() const override
	{
		m_rect->draw(getGame()->getRenderTarget());
	}


	JamTemplate::SmartShape::Sptr m_rect;
};

using ShotPtr = std::shared_ptr<Shot>;

#endif
