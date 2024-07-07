#include "state_audio.hpp"
#include <audio/sound/sound.hpp>
#include <game_interface.hpp>
#include <preload_helper.hpp>
#include <state_select.hpp>
#include <imgui.h>

void StateAudio::onCreate()
{
    // check if music was already created m_sound = getGame()->audio().getPermanentSound("music");
    if (m_sound == nullptr) {
        // create new music
        m_sound = getGame()->audio().addPermanentSound("music", "event:/test/unit/jt_test/test");
    }
}

void StateAudio::onEnter() { }

void StateAudio::onUpdate(float /*elapsed*/)
{
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Escape)) {
        getGame()->stateManager().switchState(std::make_shared<StateSelect>());
    }
}

void StateAudio::onDraw() const
{
    ImGui::Begin("Sound");
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

std::string StateAudio::getName() const { return "State Demo Audio"; }
