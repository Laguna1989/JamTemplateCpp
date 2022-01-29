#ifndef GUARD_JAMTEMPLATE_LOGGING_AUDIO_HPP
#define GUARD_JAMTEMPLATE_LOGGING_AUDIO_HPP

#include "audio_interface.hpp"
#include "logging/logger_interface.hpp"

namespace jt {
class LoggingAudio : public AudioInterface {
public:
    LoggingAudio(AudioInterface& decoratee, LoggerInterface& logger);
    std::shared_ptr<SoundInterface> createSound(std::string const& fileName) override;
    void update() override;
    void playMusic(std::string const& fileName) override;

private:
    AudioInterface& m_decoratee;
    LoggerInterface& m_logger;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOGGING_AUDIO_HPP
