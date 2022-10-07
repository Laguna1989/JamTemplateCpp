#ifndef JAMTEMPLATE_STATE_INTRO_HPP
#define JAMTEMPLATE_STATE_INTRO_HPP

#include <audio/sound_interface.hpp>
#include <game_state.hpp>
#include <sprite.hpp>
#include <memory>

class StateIntro : public jt::GameState {
private:
    std::shared_ptr<jt::Sprite> m_sprite;
    std::shared_ptr<jt::SoundInterface> m_jingle;

    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;
};

#endif // JAMTEMPLATE_STATE_INTRO_HPP
