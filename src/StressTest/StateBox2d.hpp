#ifndef STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_BOX2D_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include <Box2D/Box2D.h>

#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/SmartShape.hpp"
#include "../JamTemplate/TweenAlpha.hpp"
#include "../JamTemplate/Game.hpp"
#include "MovementObject.hpp"

class StateBox2d : public JamTemplate::GameState {
public:
	StateBox2d() : m_world{ std::make_shared<b2World>( b2Vec2{0,0.02}) }
	{

	}

private:

	std::shared_ptr<b2World> m_world{nullptr};

	void doInternalUpdate(float const /*elapsed*/) override;

	void doCreate() override
	{
		b2BodyDef groundBodyDef;
		groundBodyDef.fixedRotation = true;
		{
			groundBodyDef.position.Set(32, 100-16);
			MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
			add(b2obj);
		}
		{
			groundBodyDef.position.Set(48, 100);
			MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
			add(b2obj);
		}
		{
			groundBodyDef.position.Set(64, 100);
			MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
			add(b2obj);
		}
		{
			groundBodyDef.position.Set(80, 100);
			MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
			add(b2obj);
		}
		{
			groundBodyDef.position.Set(96, 100);
			MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
			add(b2obj);
		}
		{
			groundBodyDef.position.Set(112, 100-16);
			MovementObject::Sptr b2obj = std::make_shared<MovementObject>(m_world, &groundBodyDef);
			add(b2obj);
		}

		b2BodyDef bodyDef;
		bodyDef.fixedRotation = true;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(48, 0.0f);
		MovementObject::Sptr myBody = std::make_shared<MovementObject>(m_world, &bodyDef);
		
		add(myBody);
	}
};

#endif
