#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include "JamTemplate/GameState.hpp"
#include "Player.hpp"

class StateGame : public JamTemplate::GameState {
public:
		StateGame()
	{
		std::cout << "game ctor" << std::endl;
	}

private:
	void doUpdate(float const elapsed) override
	{
		std::cout << "game update\n";

	}

	void doCreate() override
	{
		m_player = std::make_shared<Player>();
		add(m_player);
	}

	std::shared_ptr<Player> m_player;
};

#endif