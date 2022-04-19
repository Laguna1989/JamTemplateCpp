#include "state_audio.hpp"
#include <audio/sound_group.hpp>
#include <game_interface.hpp>
#include <state_select.hpp>
#include <imgui.h>

void StateAudio::doInternalCreate()
{
    // check if music was already created
    m_sound = getGame()->audio().getPermanentSound("music");
    if (m_sound == nullptr) {
        // create new music
        m_sound = getGame()->audio().addPermanentSound(
            "music", "assets/demos/audio/looping_stereo_track.mp3", m_effect);
        m_sound->setLoop(true);
    } else {
        // get blend property from already created music
        m_blend = m_sound->getBlend();
    }

    auto soundGroup = std::make_shared<jt::SoundGroup>();
    std::map<std::string, float> pitches { { "A3", 0.5f }, { "A4", 1.0f },
        { "B4", 1.12234772727272727273f }, { "C5", 1.18920681818181818182f },
        { "D5", 1.33484090909090909091f }, { "E5", 1.49830681818181818182f }, { "F5", 1.5874f },
        { "G5", 1.78179772727272727273f }, { "A5", 2.0f } };

    for (auto const& kvp : pitches) {
        auto snd = getGame()->audio().addTemporarySound("assets/test.ogg");
        snd->setPitch(kvp.second);
        soundGroup->add(snd);
        m_notes[kvp.first] = snd;
    }
    m_soundGroup = soundGroup;
}

void StateAudio::doInternalUpdate(float /*elapsed*/)
{
    if (m_sound->getBlend() != m_blend) {
        m_sound->setBlend(m_blend);
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateAudio::doInternalDraw() const
{
    ImGui::Begin("Sound");
    ImGui::SliderFloat("blend", &m_blend, 0.0f, 1.0f);
    if (ImGui::Button("play looping")) {
        // create new music
        m_sound = getGame()->audio().addPermanentSound(
            "music", "assets/demos/audio/looping_stereo_track.mp3", m_effect);
        m_sound->setLoop(true);
        m_sound->play();
    }
    if (ImGui::Button("play intro + looping")) {
        // create new music
        m_sound = getGame()->audio().addPermanentSound(
            "music", "assets/demos/audio/intro.ogg", "assets/demos/audio/loop.ogg", m_effect);
        m_sound->play();
    }
    if (ImGui::Button("pause")) {
        m_sound->pause();
    }
    if (ImGui::Button("stop")) {
        m_sound->stop();
    }
    ImGui::Separator();
    ImGui::Text("SoundGroup");
    if (ImGui::Button("play One Sound")) {
        m_soundGroup->play();
    }
    ImGui::Separator();
    for (auto const& kvp : m_notes) {
        if (ImGui::Button(kvp.first.c_str())) {
            kvp.second->play();
        }
    }
    ImGui::End();
}
