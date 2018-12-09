#ifndef GAME_STATE_MENU_HPP_INCLUDEGUARD
#define GAME_STATE_MENU_HPP_INCLUDEGUARD

#include <iostream>
#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/Game.hpp"
#include "../JamTemplate/Timer.hpp"
#include "../JamTemplate/SmartShape.hpp"
#include "../JamTemplate/Random.hpp"

#include "Object.hpp"

class State1 : public JamTemplate::GameState {
public:
	State1() = default;
private:
	void doInternalUpdate(float const /*elapsed*/) override;

	void doCreate()
	{
		using JamTemplate::Timer;
		
		getGame()->shake(0.5f, 2.0f);
		JamTemplate::Timer::Sptr  t = std::make_shared<Timer>(0.6f, [this]() {getGame()->shake(0.5f,2.0f); });
		add(t);

	}
};

#endif
