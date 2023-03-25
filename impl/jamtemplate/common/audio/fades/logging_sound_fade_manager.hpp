#ifndef JAMTEMPLATE_LOGGING_SOUND_FADE_MANAGER_HPP
#define JAMTEMPLATE_LOGGING_SOUND_FADE_MANAGER_HPP

#include <audio/fades/sound_fade_manager_interface.hpp>
#include <log/logger_interface.hpp>

namespace jt {

class LoggingSoundFadeManager : public jt::SoundFadeManagerInterface {
public:
    LoggingSoundFadeManager(SoundFadeManagerInterface& decoratee, LoggerInterface& logger);
    void volumeFade(std::weak_ptr<SoundInterface> sound, float durationInSeconds, float startVolume,
        float endVolume) override;
    void update(float elapsed) override;
    size_t size() const override;

private:
    SoundFadeManagerInterface& m_decoratee;
    LoggerInterface& m_logger;
};

} // namespace jt

#endif // JAMTEMPLATE_LOGGING_SOUND_FADE_MANAGER_HPP
