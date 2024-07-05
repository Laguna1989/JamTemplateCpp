#ifndef JAMTEMPLATE_STATE_INTRO_HPP
#define JAMTEMPLATE_STATE_INTRO_HPP

#include <audio/sound/sound_interface.hpp>
#include <game_state.hpp>
#include <sprite.hpp>
#include <memory>

class StateIntro : public jt::GameState {
private:
    std::shared_ptr<jt::Sprite> m_runvsLogo;
    std::shared_ptr<jt::Sprite> m_fmodLogo;
    std::shared_ptr<jt::SoundInterface> m_jingle;

    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;
};

#endif // JAMTEMPLATE_STATE_INTRO_HPP
