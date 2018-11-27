#ifndef GAME_STATE_GAME_HPP_INCLUDEGUARD
#define GAME_STATE_GAME_HPP_INCLUDEGUARD

#include <iostream>
#include "JamTemplate/GameState.hpp"

class StateGame : public JamTemplate::GameState {
public:
		StateGame()
	{
		std::cout << "game ctor" << std::endl;
	}

	void doUpdate(float const elapsed) override
	{
		std::cout << "game update\n";

	}
};

#endif