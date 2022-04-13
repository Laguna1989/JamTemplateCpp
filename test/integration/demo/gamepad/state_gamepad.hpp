#ifndef JAMTEMPLATE_STATE_GAMEPAD_HPP
#define JAMTEMPLATE_STATE_GAMEPAD_HPP

#include <game_state.hpp>

class StateGamepad : public jt::GameState {
private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
};

#endif // JAMTEMPLATE_STATE_GAMEPAD_HPP
