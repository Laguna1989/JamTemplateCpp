#ifndef STRESSTEST_MOVEMENTOBJECT_HPP_INCLUDEGUARD
#define STRESSTEST_MOVEMENTOBJECT_HPP_INCLUDEGUARD

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>
#include <random>

#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/Game.hpp"
#include "../JamTemplate/Random.hpp"
#include "../JamTemplate/Transform.hpp"
#include "../JamTemplate/SmartShape.hpp"
#include "../JamTemplate/Animation.hpp"
#include "../JamTemplate/MathHelper.hpp"
#include "../JamTemplate/ObjectGroup.hpp"
#include "../JamTemplate/Box2DObject.hpp"
#include "../JamTemplate/Conversions.hpp"

class MovementObject : public JamTemplate::Box2DObject {
public:
	using Sptr = std::shared_ptr<MovementObject>;
	MovementObject(std::shared_ptr<b2World> world, const b2BodyDef* def) : Box2DObject{world, def}
	{
		m_animation = std::make_shared<JamTemplate::Animation>();
		
		m_animation->add("assets/coin.png", "idle", sf::Vector2u{ 16,16 }, JamTemplate::MathHelper::vectorBetween(0U, 11U), JamTemplate::Random::getFloat(0.13f,0.17f));
		m_animation->play("idle", JamTemplate::Random::getInt(0,6));
		m_animation->setOffset(sf::Vector2f{-8,-8});
		m_animation->setOrigin(sf::Vector2f{8,8});

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(8, 8);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.9f;

		getB2Body()->CreateFixture(&fixtureDef);
	}

	~MovementObject() = default;

	std::shared_ptr<JamTemplate::Animation> getAnimation()
	{
		return m_animation;
	}

	
private:

	std::shared_ptr<JamTemplate::Animation> m_animation;
	
	void doUpdate(float const elapsed) override
	{
		using JamTemplate::C;
		m_animation->setPosition( C::vec(getB2Body()->GetPosition()));
		
		m_animation->update(elapsed);
		if (getB2Body()->GetType() == b2BodyType::b2_dynamicBody)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			{
				getB2Body()->ApplyForceToCenter(b2Vec2{1000,0},true);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			{
				getB2Body()->ApplyForceToCenter(b2Vec2{ -1000,0 }, true);
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::B))
		{
			m_animation->flash(0.5f, sf::Color::Red);
		}
		
	}

	void doDraw() const override
	{
		

		m_animation->draw(getGame()->getRenderTarget());
	}

};


#endif
