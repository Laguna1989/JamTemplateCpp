#ifndef GAME_PLAYER_SOUND_COMPONENT_HPP
#define GAME_PLAYER_SOUND_COMPONENT_HPP

#include <audio/audio_interface.hpp>
#include <log/logger_interface.hpp>
#include <player/sound/sound_component_interface.hpp>

namespace jt {
class SoundGroup;
}

class SoundComponentImpl : public SoundComponentInterface {
public:
    SoundComponentImpl(jt::AudioInterface& audio, jt::LoggerInterface& logger);
    void play(SoundId sound) override;
    bool isPlaying(SoundId sound) override;

private:
    std::shared_ptr<jt::SoundInterface> m_soundDash;
    std::shared_ptr<jt::SoundInterface> m_soundStomp;
    std::shared_ptr<jt::SoundInterface> m_soundDeath;
    std::shared_ptr<jt::SoundGroup> m_soundGroupHurt;
};

#endif // GAME_PLAYER_SOUND_COMPONENT_HPP
