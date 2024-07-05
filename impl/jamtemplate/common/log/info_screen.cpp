#include "info_screen.hpp"
#include <game_interface.hpp>
#include <imgui.h>

jt::InfoScreen::InfoScreen()
{
#ifdef JT_ENABLE_DEBUG
    m_frameTimesVector.resize(m_frameTimes.capacity());
    m_GameObjectAliveCountVector.resize(m_GameObjectAliveCount.capacity());
#endif
}

void jt::InfoScreen::doUpdate(float const elapsed)
{
#ifdef JT_ENABLE_DEBUG
    m_numberOfUpdatesInThisFrame++;
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::End)) {
        m_showInfo = !m_showInfo;
    }

    m_frameTimes.put(elapsed);

    auto const pushIndex = m_frameTimes.getTail();
    for (auto index = pushIndex; index != pushIndex + m_frameTimes.capacity(); ++index) {
        m_frameTimesVector[index - pushIndex] = m_frameTimes[index];
    }

    m_GameObjectAliveCount.put(static_cast<float>(getNumberOfAliveGameObjects()));
    auto const pushIndex2 = m_GameObjectAliveCount.getTail();
    for (auto index = pushIndex2; index != pushIndex2 + m_GameObjectAliveCount.capacity();
         ++index) {
        m_GameObjectAliveCountVector[index - pushIndex2] = m_GameObjectAliveCount[index];
    }
#endif
}

void jt::InfoScreen::doDraw() const
{
#ifdef JT_ENABLE_DEBUG
    m_numberOfUpdatesInLastFrame.put(m_numberOfUpdatesInThisFrame);
    m_numberOfUpdatesInThisFrame = 0;

    if (!m_showInfo) {
        return;
    }
    ImGui::Begin("Debug Info");
    if (!ImGui::CollapsingHeader("Textures")) {
        std::string textures
            = "# Textures stored: " + std::to_string(textureManager().getNumberOfTextures());
        ImGui::Text("%s", textures.c_str());
    }
    if (!ImGui::CollapsingHeader("Performance")) {

        ImGui::PlotLines("Frame Time [s]", m_frameTimesVector.data(),
            static_cast<int>(m_frameTimesVector.size()), 0, nullptr, 0, FLT_MAX, ImVec2 { 0, 100 });

        ImGui::PlotLines("Updates per Frame", m_numberOfUpdatesInLastFrame.data(),
            static_cast<int>(m_numberOfUpdatesInLastFrame.capacity()), 0, nullptr, 0, FLT_MAX,
            ImVec2 { 0, 100 });
    }
    if (!ImGui::CollapsingHeader("GameStates")) {
        auto const states = getGame()->stateManager().getStoredStateIdentifiers();
        ImGui::Text("Stored States: %zu", states.size());
        for (auto const& s : states) {
            ImGui::Text("   %s", s.c_str());
        }
    }
    if (!ImGui::CollapsingHeader("GameState")) {
        auto const state = getGame()->stateManager().getCurrentState();
        ImGui::Text("%s", state->getName().c_str());
        std::string const gameStateAge
            = "Age: " + jt::MathHelper::floatToStringWithXDecimalDigits(state->getAge(), 2) + " s";
        ImGui::Text("%s", gameStateAge.c_str());

        std::string const gameObjectsInThisStateText
            = "# GameObjects (in state): " + std::to_string(state->getNumberOfObjects());
        ImGui::Text("%s", gameObjectsInThisStateText.c_str());

        std::string const totalGameObjectsText
            = "# GameObjects (total): " + std::to_string(getNumberOfAliveGameObjects());
        ImGui::Text("%s", totalGameObjectsText.c_str());

        std::string const createdGameObjectsText
            = "# GameObjects (created): " + std::to_string(getNumberOfCreatedGameObjects());
        ImGui::Text("%s", createdGameObjectsText.c_str());

        ImGui::PlotLines("AliveGameObjects [#]", m_GameObjectAliveCountVector.data(),
            static_cast<int>(m_GameObjectAliveCountVector.size()), 0, nullptr, 0, FLT_MAX,
            ImVec2 { 0, 100 });

        ImGui::Separator();
        std::string const createdSoundsText
            = "# Sounds (created): " + std::to_string(jt::Sound::createdObjects());
        std::string const aliveSoundsText
            = "# Sounds (alive): " + std::to_string(jt::Sound::aliveObjects());

        ImGui::Text("%s", createdSoundsText.c_str());
        ImGui::Text("%s", aliveSoundsText.c_str());
    }
    ImGui::End();
#endif
}
