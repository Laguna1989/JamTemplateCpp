#ifndef GUARD_JAMTEMPLATE_STATE_AUDIO_HPP
#define GUARD_JAMTEMPLATE_STATE_AUDIO_HPP

#include "audio/sound_with_effect.hpp"
#include "game_state.hpp"
#include "oalpp/effects/filter/butterworth_24db_lowpass.hpp"
#include <map>
#include <memory>
#include <optional>

class StateAudio : public jt::GameState {
private:
    void doInternalCreate() override;
    void doInternalUpdate(float elapsed) override;
    void doInternalDraw() const override;

    oalpp::effects::filter::Butterworth24dbLowpass m_effect { 44100, 600.0f, 0.2f };
    std::shared_ptr<jt::SoundInterface> m_sound { nullptr };

    std::shared_ptr<jt::SoundInterface> m_soundGroup { nullptr };
    std::map<std::string, std::shared_ptr<jt::SoundInterface>> m_notes;

    mutable float m_blend { 0.0f };
};

#endif // GUARD_JAMTEMPLATE_STATE_AUDIO_HPP
