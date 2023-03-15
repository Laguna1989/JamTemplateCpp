#ifndef JAMTEMPLATE_STATE_TRANSITIONS_HPP
#define JAMTEMPLATE_STATE_TRANSITIONS_HPP

#include <game_state.hpp>

class StateTransitions : public jt::GameState {
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;
};

#endif // JAMTEMPLATE_STATE_TRANSITIONS_HPP
