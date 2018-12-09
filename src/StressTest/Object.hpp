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
		m_shape->setColor(JamTemplate::Random::getRandomColor());

		float x = JamTemplate::Random::getFloat(30, 200 - 24);
		float y = JamTemplate::Random::getFloat(30, 150 - 24);
		
		float vx = JamTemplate::Random::getFloatGauss(0,50);
		float vy = JamTemplate::Random::getFloatGauss(0, 50);

		setPosition({ x, y });
		setVelocity({ vx,vy });
		//setAcceleration({ 0, -50 / 2 });
		setBoundsPosition(sf::FloatRect{ 0,0,200-10,150-10 });
		
	}

	~Object() = default;

	void Flash()
	{
		m_shape->flash(0.1f);
	}
	void Shake()
	{
		m_shape->shake(0.5f, 2.0f,0.05f);
	}
	
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
