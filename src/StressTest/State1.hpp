#ifndef GAME_STATE_MENU_HPP_INCLUDEGUARD
#define GAME_STATE_MENU_HPP_INCLUDEGUARD

#include <iostream>
#include "../JamTemplate/GameState.hpp"
#include "../JamTemplate/Game.hpp"
#include "../JamTemplate/Timer.hpp"
#include "../JamTemplate/SmartShape.hpp"

#include "Object.hpp"

class State1 : public JamTemplate::GameState {
public:
	State1() = default;
private:
	void doInternalUpdate(float const /*elapsed*/) override;

	void doCreate()
	{
		unsigned int N = 1;
		for (unsigned int i = 0; i != N; ++i)
		{
			Object::Sptr bp = std::make_shared<Object>();
			add(bp);

			JamTemplate::Timer::Sptr t = std::make_shared<JamTemplate::Timer>(JamTemplate::Random::getFloat(0.125, 3), [bp]() {bp->Flash(); bp->Shake(); });
			add(t);

		}
	}
};

#endif
