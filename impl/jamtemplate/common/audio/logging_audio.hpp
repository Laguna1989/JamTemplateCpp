#ifndef JAMTEMPLATE_LOGGING_AUDIO_HPP
#define JAMTEMPLATE_LOGGING_AUDIO_HPP

#include <audio/audio_interface.hpp>
#include <log/logger_interface.hpp>

namespace jt {
class LoggingAudio : public AudioInterface {
public:
    LoggingAudio(AudioInterface& decoratee, LoggerInterface& logger);

    void update(float elapsed) override;

    std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& fileName) override;
    std::shared_ptr<jt::SoundInterface> addTemporarySoundGroup(
        std::vector<std::shared_ptr<jt::SoundInterface>> const& sounds) override;

    std::shared_ptr<jt::SoundInterface> addPermanentSound(
        std::string const& identifier, std::string const& fileName) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& fileName, oalpp::effects::MonoEffectInterface& effect) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& introFileName, std::string const& loopingFileName,
        oalpp::effects::MonoEffectInterface& effect) override;

    std::shared_ptr<SoundInterface> soundPool(
        std::string const& baseIdentifier, std::string const& fileName, std::size_t count) override;

    std::shared_ptr<SoundInterface> getPermanentSound(std::string const& identifier) override;

    void removePermanentSound(std::string const& identifier) override;

    oalpp::SoundContextInterface& getContext() override;

    SoundFadeManager& fades() override;
    GroupVolumeSetterInterface& groups() override;

private:
    AudioInterface& m_decoratee;
    LoggerInterface& m_logger;
};
} // namespace jt

#endif // JAMTEMPLATE_LOGGING_AUDIO_HPP
