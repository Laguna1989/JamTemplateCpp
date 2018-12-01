#ifndef GAME_STATE_MENU_HPP_INCLUDEGUARD
#define GAME_STATE_MENU_HPP_INCLUDEGUARD

#include <iostream>
#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Game.hpp"
#include "StateGame.hpp"
class StateMenu : public JamTemplate::GameState {
public:
	StateMenu() = default;
private:
	void doInternalUpdate (float const elapsed) override 
	{
		if (getAge() >= 0.25)
		{
			getGame()->switchState(std::make_shared<StateGame>());
		}
		
	}
};

#endif
