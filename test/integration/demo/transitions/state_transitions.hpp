#ifndef GUARD_JAMTEMPLATE_STATE_TRANSITIONS_HPP
#define GUARD_JAMTEMPLATE_STATE_TRANSITIONS_HPP

#include "game_state.hpp"

class StateTransitions : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
};

#endif // GUARD_JAMTEMPLATE_STATE_TRANSITIONS_HPP