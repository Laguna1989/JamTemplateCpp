#ifndef GUARD_JAMTEMPLATE_STATE_IMGUI_HPP
#define GUARD_JAMTEMPLATE_STATE_IMGUI_HPP

#include "game_state.hpp"
#include <string>

class StateImGui : public ::jt::GameState {
public:
    std::string getName() const override;

private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
};

#endif // GUARD_JAMTEMPLATE_STATE_IMGUI_HPP
