#ifndef STRESSTEST_STATE_1_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_1_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "Object.hpp"
#include "Random.hpp"
#include "SmartShape.hpp"
#include "Timer.hpp"
#include <iostream>

class State1 : public JamTemplate::GameState {
public:
    State1() = default;

private:
    void doInternalUpdate(float const /*elapsed*/) override;

    void doCreate()
    {
        using JamTemplate::Timer;

        getGame()->shake(0.5f, 2.0f);
        JamTemplate::Timer::Sptr t
            = std::make_shared<Timer>(0.6f, [this]() { getGame()->shake(0.5f, 2.0f); });
        add(t);
    }
};

#endif
