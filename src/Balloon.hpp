#ifndef GAME_BALLOON_HPP_INCLUDEGUARD
#define GAME_BALLOON_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <random>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Game.hpp"
#include "JamTemplate/Random.hpp"

#include "JamTemplate/SmartShape.hpp"


class Balloon : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	using Sptr = std::shared_ptr<Balloon>;

	Balloon()
	{
		
		m_shape = std::make_shared<JamTemplate::SmartShape>();
		m_shape->makeCircle(12);
		m_shape->setColor(sf::Color::Red);

		float x = JamTemplate::Random::getFloat(30, 200-24);
		setPosition({ x, 200 });
		setVelocity({0, -GP::balloonMoveSpeed()});
		setAcceleration({ 0, -GP::balloonMoveSpeed() / 2 });
		setBoundsVelocity(sf::FloatRect(-GP::balloonMoveSpeed() , -GP::balloonMoveSpeed(), GP::balloonMoveSpeed()*2, GP::balloonMoveSpeed()*2));
	}

	~Balloon() = default;

	const std::shared_ptr<sf::Shape> getShape() const { return m_shape->getShape(); }
private:
	void doUpdate(float const elapsed) override
	{
		updateTransform(elapsed);
		
		m_shape->setPosition(getPosition());
		m_shape->update(elapsed);

		if (getPosition().y < -50)
		{
			kill();
		}
	}

	void doDraw() const override
	{
		m_shape->draw(getGame()->getRenderTarget());
	}

	JamTemplate::SmartShape::Sptr m_shape;
};

#endif
