#ifndef GUARD_JAMTEMPLATE_LOGGING_AUDIO_HPP
#define GUARD_JAMTEMPLATE_LOGGING_AUDIO_HPP

#include "audio_interface.hpp"
#include "logging/logger_interface.hpp"

namespace jt {
class LoggingAudio : public AudioInterface {
public:
    LoggingAudio(AudioInterface& decoratee, LoggerInterface& logger);

    void update() override;

    void addTemporarySound(std::weak_ptr<SoundInterface> snd) override;
    void addPermanentSound(
        std::string const& identifier, std::shared_ptr<SoundInterface> snd) override;

    std::shared_ptr<SoundInterface> getPermanentSound(std::string const& identifier) override;

    void removePermanentSound(std::string const& identifier) override;

    oalpp::SoundContextInterface& getContext() override;

private:
    AudioInterface& m_decoratee;
    LoggerInterface& m_logger;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOGGING_AUDIO_HPP
