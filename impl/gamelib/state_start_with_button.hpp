#pragma once

#include <button.hpp>
#include <game_state.hpp>
#include <memory>

class StateStartWithButton : public jt::GameState {
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    std::shared_ptr<jt::Button> m_button;
};
