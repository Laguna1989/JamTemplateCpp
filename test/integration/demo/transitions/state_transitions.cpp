#include "state_transitions.hpp"
#include <game_interface.hpp>
#include <state_manager/state_manager_transition_fade_to_black.hpp>
#include <state_manager/state_manager_transition_horizontal_bars.hpp>
#include <state_manager/state_manager_transition_none.hpp>
#include <state_select.hpp>
#include <imgui.h>

void StateTransitions::onCreate() { }
void StateTransitions::onEnter() { }
void StateTransitions::onUpdate(float /*elapsed*/) { }
void StateTransitions::onDraw() const
{
    ImGui::Begin("Transitions");
    if (ImGui::Button("None")) {
        getGame()->stateManager().setTransition(std::make_shared<jt::StateManagerTransitionNone>());
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
    if (ImGui::Button("Fade2Black")) {
        getGame()->stateManager().setTransition(
            std::make_shared<jt::StateManagerTransitionFadeToBlack>(
                getGame()->gfx().window().getSize(), textureManager(), 0.5f));
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
    if (ImGui::Button("Horizontal Bars")) {
        getGame()->stateManager().setTransition(
            std::make_shared<jt::StateManagerTransitionHorizontalBars>(
                jt::Vector2f {
                    getGame()->gfx().window().getSize().x / getGame()->gfx().camera().getZoom(),
                    32 },
                10, 1.0f, textureManager()));
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
    ImGui::End();
}
