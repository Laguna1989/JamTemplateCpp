#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include <vector>

#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Timer.hpp"
#include "Player.hpp"
#include "Balloon.hpp"

class StateGame : public JamTemplate::GameState {
public:
		StateGame()
	{
		std::cout << "game ctor" << std::endl;
	}

		void spawnBalloon()
		{
			add(std::make_shared<Balloon>());
		}

private:
	void doUpdate(float const elapsed) override
	{
		//std::cout << "game update\n";
		updateObjects(elapsed);
		
	}

	void doCreate() override
	{
		m_player = std::make_shared<Player>();
		add(m_player);

		auto t = std::make_shared<JamTemplate::Timer>(1.5f, [this]() {this->spawnBalloon(); }, -1);
		add(t);
	}

	std::shared_ptr<Player> m_player;
	std::vector<BalloonPtr> m_balloons;
};

#endif