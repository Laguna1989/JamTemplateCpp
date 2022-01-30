#include "state_audio.hpp"
#include "game_interface.hpp"
#include "imgui.h"

void StateAudio::doInternalCreate()
{
    m_soundWithEffect
        = getGame()->audio().createSoundWithEffect("assets/looping_stereo_track.mp3", m_effect);
    m_soundWithEffect->setLoop(true);
    m_soundWithEffect->play();
}
void StateAudio::doInternalUpdate(float elapsed) { m_soundWithEffect->setBlend(m_blend); }
void StateAudio::doInternalDraw() const
{
    ImGui::Begin("Sound");
    ImGui::SliderFloat("blend", &m_blend, 0.0f, 1.0f);
    ImGui::End();
}
