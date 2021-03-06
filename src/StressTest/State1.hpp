﻿#ifndef STRESSTEST_STATE_1_HPP_INCLUDEGUARD
#define STRESSTEST_STATE_1_HPP_INCLUDEGUARD

#include "Game.hpp"
#include "GameState.hpp"
#include "Object.hpp"
#include "Random.hpp"
#include "SmartShape.hpp"
#include "Timer.hpp"
#include <iostream>

class State1 : public jt::GameState {
private:
    void doInternalCreate() override;
    void doInternalUpdate(float const /*elapsed*/) override;
    void doInternalDraw() const override {};
};

#endif
