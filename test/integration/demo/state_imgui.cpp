#include "state_imgui.hpp"
#include "console/console.hpp"
#include "console/log.hpp"
#include "game_interface.hpp"
#include "imgui.h"
#include <iostream>

void StateImGui::doInternalCreate()
{
    m_logger = std::make_shared<jt::Log>();
    m_console = std::make_shared<jt::Console>(m_logger);
    add(m_console);
}

void StateImGui::doInternalUpdate(float elapsed)
{
    getGame()->getRenderWindow()->updateGui(elapsed);
    auto mouse = getGame()->input()->mouse();
    if (mouse->justPressed(jt::MouseButtonCode::MBLeft)) {
        m_logger->debug("mouse button pressed");
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::A)) {
        std::cout << "rmb\n";
        m_logger->error("keyboard 'A' not supported");
    }
}

void StateImGui::doInternalDraw() const
{
    getGame()->getRenderWindow()->startRenderGui();
    ImGui::ShowDemoWindow();
}
