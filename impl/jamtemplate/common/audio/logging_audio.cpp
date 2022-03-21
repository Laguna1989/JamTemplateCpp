#include "logging_audio.hpp"
#include "logging_sound.hpp"

jt::LoggingAudio::LoggingAudio(jt::AudioInterface& decoratee, jt::LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

void jt::LoggingAudio::update()
{
    m_logger.verbose("Audio update", { "jt", "audio" });
    m_decoratee.update();
}

void jt::LoggingAudio::addTemporarySound(std::weak_ptr<jt::SoundInterface> snd)
{
    m_logger.verbose("add temporary sound", { "jt", "audio" });
    m_decoratee.addTemporarySound(snd);
}

void jt::LoggingAudio::addPermanentSound(
    std::string const& identifier, std::shared_ptr<jt::SoundInterface> snd)
{
    m_logger.debug("add permanent sound: " + identifier, { "jt", "audio" });
    m_decoratee.addPermanentSound(identifier, snd);
}
std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::getPermanentSound(
    std::string const& identifier)
{
    m_logger.verbose("get permanent sound: " + identifier, { "jt", "audio" });
    return m_decoratee.getPermanentSound(identifier);
}

void jt::LoggingAudio::removePermanentSound(std::string const& identifier) { }

oalpp::SoundContextInterface& jt::LoggingAudio::getContext() { return m_decoratee.getContext(); }
std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::soundPool(std::string const& baseIdentifier,
    std::function<std::shared_ptr<jt::SoundInterface>()> function, std::size_t count)
{
    m_logger.verbose("sound pool: " + baseIdentifier, { "jt", "audio" });
    return m_decoratee.soundPool(baseIdentifier, function, count);
}
