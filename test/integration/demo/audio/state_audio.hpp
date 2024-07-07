#ifndef JAMTEMPLATE_STATE_AUDIO_HPP
#define JAMTEMPLATE_STATE_AUDIO_HPP

#include <audio/sound/sound_interface.hpp>
#include <game_state.hpp>
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

    mutable std::shared_ptr<jt::SoundInterface> m_sound { nullptr };
};

#endif // JAMTEMPLATE_STATE_AUDIO_HPP
