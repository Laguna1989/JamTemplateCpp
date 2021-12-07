#include "state_imgui.hpp"
#include "game_interface.hpp"
#include "imgui.h"
#include "logging/console.hpp"
#include "logging/logger.hpp"
#include "state_select.hpp"
#include <iostream>

void StateImGui::doInternalCreate()
{
    m_console = std::make_shared<jt::Console>(getGame()->getLogger());
    add(m_console);
}

void StateImGui::doInternalUpdate(float elapsed)
{
    getGame()->getRenderWindow()->updateGui(elapsed);
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

void StateImGui::doInternalDraw() const
{
    getGame()->getRenderWindow()->startRenderGui();
    ImGui::ShowDemoWindow();
}
std::string StateImGui::getName() const { return "Dear ImGui"; }
