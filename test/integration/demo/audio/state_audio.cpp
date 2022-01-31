#include "state_audio.hpp"
#include "../state_select.hpp"
#include "game_interface.hpp"
#include "imgui.h"

void StateAudio::doInternalCreate()
{
    // check if music was already created
    m_soundWithEffect = getGame()->audio().getPermanentSound("music");
    if (m_soundWithEffect == nullptr) {
        // create new music
        m_soundWithEffect = std::make_shared<jt::SoundWithEffect>(
            "assets/looping_stereo_track.mp3", m_effect, getGame()->audio().getContext());
        m_soundWithEffect->setLoop(true);
        m_soundWithEffect->play();
        getGame()->audio().addPermanentSound("music", m_soundWithEffect);
    } else {
        // get blend property from already created music
        m_blend = m_soundWithEffect->getBlend();
    }
}

void StateAudio::doInternalUpdate(float elapsed)
{
    m_soundWithEffect->setBlend(m_blend);
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->getStateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateAudio::doInternalDraw() const
{
    ImGui::Begin("Sound");
    ImGui::SliderFloat("blend", &m_blend, 0.0f, 1.0f);
    ImGui::End();
}
