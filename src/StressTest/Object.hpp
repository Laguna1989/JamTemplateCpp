#ifndef GAME_OBJECT_HPP_INCLUDEGUARD
#define GAME_OBJECT_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <random>

#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/Game.hpp"
#include "../JamTemplate/Random.hpp"
#include "../JamTemplate/Transform.hpp"
#include "../JamTemplate/SmartShape.hpp"

class Object : public JamTemplate::GameObject, public JamTemplate::Transform {
public:
	using Sptr = std::shared_ptr<Object>;
	Object()
	{
		m_shape = std::make_shared<JamTemplate::SmartShape>();
		m_shape->makeRect(sf::Vector2f(10, 10));
		m_shape->setColor(sf::Color::Red);

		float x = JamTemplate::Random::getFloat(30, 200 - 24);
		setPosition({ x, 200 });
		setVelocity({ 0, -50 });
		setAcceleration({ 0, -50 / 2 });
		setBoundsVelocity(sf::FloatRect(-50, -50, 50 * 2, 50 * 2));


	}

	~Object() = default;

	
private:
	void doUpdate(float const elapsed) override
	{
		updateTransform(elapsed);
		m_shape->setPosition(getPosition());

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
