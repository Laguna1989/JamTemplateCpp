#ifndef JAMTEMPLATE_STATE_GAMEPAD_HPP
#define JAMTEMPLATE_STATE_GAMEPAD_HPP

#include <game_state.hpp>

class StateGamepad : public jt::GameState {
private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;
};

#endif // JAMTEMPLATE_STATE_GAMEPAD_HPP
