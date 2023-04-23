#ifndef JAMTEMPLATE_STATE_AUDIO_HPP
#define JAMTEMPLATE_STATE_AUDIO_HPP

#include <audio/sound/sound_with_effect.hpp>
#include <game_state.hpp>
#include <oalpp/effects/filter/butterworth_24db_lowpass.hpp>
#include <map>
#include <memory>
#include <optional>

class StateAudio : public jt::GameState {
public:
    std::string getName() const override;

private:
    void onCreate() override;
    void onEnter() override;
    void onUpdate(float elapsed) override;
    void onDraw() const override;

    mutable oalpp::effects::filter::Butterworth24dbLowpass m_effect { 44100, 600.0f, 0.2f };
    mutable std::shared_ptr<jt::SoundInterface> m_sound { nullptr };

    std::shared_ptr<jt::SoundInterface> m_soundGroup { nullptr };
    std::map<std::string, std::shared_ptr<jt::SoundInterface>> m_notes;

    mutable float m_blend { 0.0f };
    mutable std::map<std::string, float> m_volumes {};
    std::shared_ptr<jt::SoundInterface> m_loopingSound { nullptr };
};

#endif // JAMTEMPLATE_STATE_AUDIO_HPP
