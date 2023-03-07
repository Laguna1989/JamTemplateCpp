#ifndef JAMTEMPLATE_STATE_IMGUI_HPP
#define JAMTEMPLATE_STATE_IMGUI_HPP

#include <arbitrary_precision_int/arbitrary_precision_int.hpp>
#include <game_state.hpp>
#include <string>

class StateImGui : public ::jt::GameState {
public:
    std::string getName() const override;

private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    mutable api::API m_api;
    mutable int number;
};

#endif // JAMTEMPLATE_STATE_IMGUI_HPP
