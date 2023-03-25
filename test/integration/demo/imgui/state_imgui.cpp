#include "state_imgui.hpp"
#include <game_interface.hpp>
#include <state_select.hpp>
#include <imgui.h>

void StateImGui::onCreate() { }

void StateImGui::onEnter() { }

void StateImGui::onUpdate(float /*elapsed*/)
{
    auto mouse = getGame()->input().mouse();
    if (mouse->justPressed(jt::MouseButtonCode::MBLeft)) {
        getGame()->logger().debug("mouse button pressed", { "Game", "other Tag" });
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::A)) {

        getGame()->logger().fatal("keyboard 'A' not supported", { "Test" });
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateImGui::onDraw() const
{
    ImGui::ShowDemoWindow();

    ImGui::Begin("arbitrary precision integers");
    ImGui::Text("%s", m_api.to_exp_string().c_str());

    ImGui::SliderInt("Value", &number, 0, 999999);
    if (ImGui::Button("add")) {
        m_api = m_api + api::from_uint64(number);
    }
    ImGui::SameLine();
    if (ImGui::Button("subtract")) {
        m_api = m_api - api::from_uint64(number);
    }
    if (ImGui::Button("multiply")) {
        m_api = m_api * api::from_uint64(number);
    }
    ImGui::SameLine();
    if (ImGui::Button("divide")) {
        m_api = m_api / api::from_uint64(number);
    }

    ImGui::End();
}
std::string StateImGui::getName() const { return "Dear ImGui"; }
