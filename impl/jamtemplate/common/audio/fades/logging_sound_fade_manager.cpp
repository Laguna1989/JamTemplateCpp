#include "logging_sound_fade_manager.hpp"

jt::LoggingSoundFadeManager::LoggingSoundFadeManager(
    SoundFadeManagerInterface& decoratee, LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

void jt::LoggingSoundFadeManager::volumeFade(std::weak_ptr<SoundInterface> sound,
    float durationInSeconds, float startVolume, float endVolume)
{
    m_logger.info("Create sound fade", { "jt", "audio", "sound fade" });
    m_decoratee.volumeFade(sound, durationInSeconds, startVolume, endVolume);
}

void jt::LoggingSoundFadeManager::update(float elapsed) {
    m_logger.verbose("sound fade manager update", { "jt", "audio", "sound fade" });
    m_decoratee.update(elapsed); }

size_t jt::LoggingSoundFadeManager::size() const {
    m_logger.verbose("sound fade manager size", { "jt", "audio", "sound fade" });
    return m_decoratee.size(); }
