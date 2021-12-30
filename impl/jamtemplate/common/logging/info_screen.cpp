#include "info_screen.hpp"
#include "game_interface.hpp"
#include "imgui.h"

namespace jt {
void InfoScreen::doCreate() { m_frameTimesVector.resize(m_frameTimes.size()); }
void InfoScreen::doUpdate(float const elapsed)
{
#ifdef JT_ENABLE_DEBUG
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::End)) {
        m_showInfo = !m_showInfo;
    }

    m_frameTimes.push(elapsed);
    auto const pushIndex = m_frameTimes.getPushIndex();
    for (auto index = pushIndex; index != pushIndex + m_frameTimes.size(); ++index) {
        m_frameTimesVector[index - pushIndex] = m_frameTimes[index];
    }
#endif
}
void InfoScreen::doDraw() const
{
    if (!m_showInfo) {
        return;
    }
    ImGui::Begin("Debug Info");
    if (!ImGui::CollapsingHeader("Textures")) {
        std::string textures = "# Textures stored: "
            + std::to_string(getGame()->gfx().textureManager().getNumberOfTextures());
        ImGui::Text(textures.c_str());
    }
    if (!ImGui::CollapsingHeader("Performance")) {

        ImGui::PlotLines("Frame Time [s]", m_frameTimesVector.data(),
            static_cast<int>(m_frameTimesVector.size()), 0, nullptr, 0, FLT_MAX, ImVec2 { 0, 100 });
    }
    if (!ImGui::CollapsingHeader("GameState")) {
        auto const state = getGame()->getStateManager().getCurrentState();
        ImGui::Text(state->getName().c_str());
        std::string const gameStateAge
            = "Age: " + jt::MathHelper::floatToStringWithXDigits(state->getAge(), 2) + " s";
        ImGui::Text(gameStateAge.c_str());
        std::string const gameObjectsText
            = "# GameObjects: " + std::to_string(state->getNumberOfObjects());
        ImGui::Text(gameObjectsText.c_str());
    }
    ImGui::End();
}
} // namespace jt
