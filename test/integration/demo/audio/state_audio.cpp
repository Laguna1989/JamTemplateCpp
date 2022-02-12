#include "state_audio.hpp"
#include "../state_select.hpp"
#include "audio/logging_sound.hpp"
#include "game_interface.hpp"
#include "imgui.h"

void StateAudio::doInternalCreate()
{
    // check if music was already created
    m_sound = getGame()->audio().getPermanentSound("music");
    if (m_sound == nullptr) {
        // create new music
        m_sound = std::make_shared<jt::LoggingSound>(
            std::make_shared<jt::SoundWithEffect>("assets/looping_stereo_track.mp3", m_effect),
            getGame()->getLogger());
        m_sound->setLoop(true);
        m_sound->play();
        getGame()->audio().addPermanentSound("music", m_sound);
    } else {
        // get blend property from already created music
        m_blend = m_sound->getBlend();
    }
}

void StateAudio::doInternalUpdate(float elapsed)
{
    if (m_sound->getBlend() != m_blend) {
        m_sound->setBlend(m_blend);
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateAudio::doInternalDraw() const
{
    ImGui::Begin("Sound");
    ImGui::SliderFloat("blend", &m_blend, 0.0f, 1.0f);
    if (ImGui::Button("play")) {
        m_sound->play();
    }
    if (ImGui::Button("pause")) {
        m_sound->pause();
    }
    if (ImGui::Button("stop")) {
        m_sound->stop();
    }
    ImGui::End();
}
