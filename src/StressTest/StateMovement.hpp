#ifndef STRESSTEST_STATE_MOVEMENT_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_MOVEMENT_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/SmartShape.hpp"
#include "../JamTemplate/Game.hpp"
#include "../JamTemplate/ObjectGroup.hpp"
#include "MovementObject.hpp"

class StateMovement : public JamTemplate::GameState {
public:
	StateMovement() = default;

private:
	MovementObject::Sptr player;
	JamTemplate::ObjectGroup<MovementObject>::Sptr m_walls;

	void doInternalUpdate(float const /*elapsed*/) override;

	void doCreate() override
	{
		

		player = std::make_shared<MovementObject>(false);
		add(player);

		m_walls = std::make_shared< JamTemplate::ObjectGroup<MovementObject>>();
		add(m_walls);
		auto leftWall = std::make_shared<MovementObject>(true);
		leftWall->setPosition(sf::Vector2f{30, 100});
		m_walls->push_back(leftWall);
		add(leftWall);
		std::cout << m_walls->size() << std::endl;
		
		player->setColliders(m_walls);
		
	}

	void doDraw() const override
	{
		drawObjects();
		
	}

};

#endif
