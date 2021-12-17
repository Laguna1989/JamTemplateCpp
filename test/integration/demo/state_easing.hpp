#ifndef GUARD_JAMTEMPLATE_STATE_EASING_HPP
#define GUARD_JAMTEMPLATE_STATE_EASING_HPP

#include "game_state.hpp"

class StateEasing : public jt::GameState {
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
};

#endif // MYAWESOMEGAME_STATE_EASING_HPP
