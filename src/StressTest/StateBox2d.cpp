#include "StateBox2d.hpp"
#include "State1.hpp"

void StateBox2d::doInternalUpdate(float const elapsed)  
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	for (int32 i = 0; i < 60; ++i)
	{
		m_world->Step(elapsed, velocityIterations, positionIterations);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F1))
	{
		getGame()->switchState(std::make_shared<State1>());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F2))
	{
		getGame()->switchState(std::make_shared<StateBox2d>());
	}
}
