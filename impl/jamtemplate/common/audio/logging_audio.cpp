#include "logging_audio.hpp"
#include "logging_sound.hpp"
namespace jt {

LoggingAudio::LoggingAudio(AudioInterface& decoratee, LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

void LoggingAudio::update()
{
    m_logger.verbose("Audio update", { "jt", "audio" });
    m_decoratee.update();
}

void LoggingAudio::addTemporarySound(std::weak_ptr<SoundInterface> snd)
{
    m_logger.debug("add temporary sound", { "jt", "audio" });
    m_decoratee.addTemporarySound(snd);
}

void LoggingAudio::addPermanentSound(
    std::string const& identifier, std::shared_ptr<SoundInterface> snd)
{
    m_logger.debug("add permanent sound: " + identifier, { "jt", "audio" });
    m_decoratee.addPermanentSound(identifier, snd);
}
std::shared_ptr<SoundInterface> LoggingAudio::getPermanentSound(std::string const& identifier)
{
    return m_decoratee.getPermanentSound(identifier);
}

void LoggingAudio::removePermanentSound(std::string const& identifier) { }

oalpp::SoundContextInterface& LoggingAudio::getContext() { return m_decoratee.getContext(); }

} // namespace jt
