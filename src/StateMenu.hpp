#ifndef GAME_STATE_MENU_HPP_INCLUDEGUARD
#define GAME_STATE_MENU_HPP_INCLUDEGUARD

#include <iostream>
#include "JamTemplate/GameState.hpp"
#include "JamTemplate/Game.hpp"
#include "StateGame.hpp"
class StateMenu : public JamTemplate::GameState {
public:
	StateMenu()
	{
		std::cout << "menu ctor" << std::endl;
	}
private:
	void doUpdate(float const elapsed) override 
	{
		std::cout << "menu update. T= "  << getAge()  << "\n";

		if (getAge() >= 5)
		{
			m_Game.lock()->SwitchState(std::make_shared<StateGame>());
		}
		
	}
};

#endif