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
            "music", "assets/test/integration/demo/looping_stereo_track.mp3", m_effect);
        m_sound->setVolumeGroup("music");
        m_sound->setLoop(true);
    } else {
        // get blend property from already created music
        m_blend = m_sound->getBlend();
    }

    std::vector<std::shared_ptr<jt::SoundInterface>> soundGroupSounds {};
    std::map<std::string, float> pitches { { "A3", 0.5f }, { "A4", 1.0f },
        { "B4", 1.12234772727272727273f }, { "C5", 1.18920681818181818182f },
        { "D5", 1.33484090909090909091f }, { "E5", 1.49830681818181818182f }, { "F5", 1.5874f },
        { "G5", 1.78179772727272727273f }, { "A5", 2.0f } };

    for (auto const& kvp : pitches) {
        auto sound = getGame()->audio().addTemporarySound("assets/test/integration/demo/test.ogg");
        sound->setPitch(kvp.second);
        sound->setVolumeGroup("blip");
        soundGroupSounds.push_back(sound);
        m_notes[kvp.first] = sound;
    }
    m_soundGroup = getGame()->audio().addTemporarySoundGroup(soundGroupSounds);
}

void StateAudio::doInternalUpdate(float /*elapsed*/)
{
    for (auto const& kvp : m_volumes) {
        getGame()->audio().groups().setGroupVolume(kvp.first, kvp.second);
    }

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
    ImGui::Text("Volume Groups");
    auto const groupNames = getGame()->audio().groups().getAllGroupNames();
    for (auto const& n : groupNames) {
        if (m_volumes.count(n) == 0) {
            m_volumes[n] = 1.0f;
        }
        auto const str = "volume '" + n + "'";
        ImGui::SliderFloat(str.c_str(), &m_volumes[n], 0.0f, 1.0f);
    }
    ImGui::Separator();
    ImGui::SliderFloat("blend", &m_blend, 0.0f, 1.0f);
    if (ImGui::Button("play looping")) {
        // create new music
        m_sound = getGame()->audio().addPermanentSound(
            "music", "assets/test/integration/demo/looping_stereo_track.mp3", m_effect);
        m_sound->setLoop(true);
        m_sound->setVolumeGroup("music");
        m_sound->play();
    }
    if (ImGui::Button("play intro + looping")) {
        // create new music
        m_sound = getGame()->audio().addPermanentSound("music",
            "assets/test/integration/demo/intro.ogg", "assets/test/integration/demo/loop.ogg",
            m_effect);
        m_sound->play();
    }
    if (ImGui::Button("pause")) {
        m_sound->pause();
    }
    if (ImGui::Button("stop")) {
        m_sound->stop();
    }
    if (ImGui::Button("Fade Out")) {
        getGame()->audio().fades().volumeFade(m_sound, 1.0f, m_sound->getVolume(), 0.0f);
    }
    if (ImGui::Button("Fade In")) {
        getGame()->audio().fades().volumeFade(m_sound, 1.0f, m_sound->getVolume(), 1.0f);
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
std::string StateAudio::getName() const { return "State Demo Audio"; }
