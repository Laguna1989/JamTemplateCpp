#include "state_store_gamestate.hpp"
#include <state_manager/state_manager_transition_none.hpp>
#include <state_select.hpp>
#include <imgui.h>

void StateStoreGamestate::onCreate() { }
void StateStoreGamestate::onEnter() { }
void StateStoreGamestate::onUpdate(float /*elapsed*/) { }
void StateStoreGamestate::onDraw() const
{
    ImGui::Begin("Store Gamestate");

    ImGui::SliderInt("value", &m_value, 0, 100);
    ImGui::Separator();

    auto newState = getGame()->stateManager().getStoredState("storeA");
    if (ImGui::Button("Store State")) {
        getGame()->stateManager().storeCurrentState("storeA");
    }
    ImGui::BeginDisabled(newState == nullptr);
    if (ImGui::Button("Load State")) {
        getGame()->stateManager().switchToStoredState("storeA");
    }
    ImGui::EndDisabled();
    if (ImGui::Button("Leave")) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
    if (ImGui::Button("Reenter")) {
        if (newState == nullptr) {
            getGame()->stateManager().switchState(std::make_shared<StateStoreGamestate>());
        } else {
            getGame()->stateManager().switchToStoredState("storeA");
        }
    }

    if (ImGui::Button("Clear")) {
        getGame()->stateManager().clearStoredState("storeA");
    }

    ImGui::End();
}
std::string StateStoreGamestate::getName() const { return "Demo State Store"; }
