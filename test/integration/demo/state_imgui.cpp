#include "state_imgui.hpp"
#include "game_interface.hpp"
#include "imgui.h"
#include "state_select.hpp"

void StateImGui::doInternalCreate() { }

void StateImGui::doInternalUpdate(float elapsed)
{
    auto mouse = getGame()->input()->mouse();
    if (mouse->justPressed(jt::MouseButtonCode::MBLeft)) {
        getGame()->getLogger()->debug("mouse button pressed", { "Game", "other Tag" });
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::A)) {

        getGame()->getLogger()->fatal("keyboard 'A' not supported", { "Test" });
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager()->switchState(std::make_shared<StateSelect>());
    }
}

void StateImGui::doInternalDraw() const { ImGui::ShowDemoWindow(); }
std::string StateImGui::getName() const { return "Dear ImGui"; }
