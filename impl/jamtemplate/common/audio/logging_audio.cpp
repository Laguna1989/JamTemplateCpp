#include "logging_audio.hpp"
#include <audio/logging_sound.hpp>

jt::LoggingAudio::LoggingAudio(jt::AudioInterface& decoratee, jt::LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

void jt::LoggingAudio::update(float elapsed)
{
    m_logger.verbose("Audio update(" + std::to_string(elapsed) + ")", { "jt", "audio" });
    m_decoratee.update(elapsed);
}

std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::getPermanentSound(
    std::string const& identifier)
{
    m_logger.verbose("get permanent sound: " + identifier, { "jt", "audio" });
    return m_decoratee.getPermanentSound(identifier);
}

void jt::LoggingAudio::removePermanentSound(std::string const& identifier)
{
    m_logger.debug("remove permanent sound: " + identifier, { "jt", "audio" });
    m_decoratee.removePermanentSound(identifier);
}

oalpp::SoundContextInterface& jt::LoggingAudio::getContext() { return m_decoratee.getContext(); }

std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::soundPool(
    std::string const& baseIdentifier, std::string const& fileName, std::size_t count)
{
    m_logger.debug("sound pool: " + baseIdentifier, { "jt", "audio" });
    return std::make_shared<jt::LoggingSound>(
        m_decoratee.soundPool(baseIdentifier, fileName, count), m_logger);
}

std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::addTemporarySound(std::string const& fileName)
{
    m_logger.debug("add temporary sound", { "jt", "audio" });
    return std::make_shared<jt::LoggingSound>(m_decoratee.addTemporarySound(fileName), m_logger);
}

std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::addPermanentSound(
    std::string const& identifier, std::string const& fileName)
{
    m_logger.debug("add permanent sound: " + identifier, { "jt", "audio" });
    return std::make_shared<jt::LoggingSound>(
        m_decoratee.addPermanentSound(identifier, fileName), m_logger);
}

std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::addPermanentSound(
    std::string const& identifier, std::string const& fileName,
    oalpp::effects::MonoEffectInterface& effect)
{
    m_logger.debug("add permanent sound with effect: " + identifier, { "jt", "audio" });
    return std::make_shared<jt::LoggingSound>(
        m_decoratee.addPermanentSound(identifier, fileName, effect), m_logger);
}
std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::addPermanentSound(
    std::string const& identifier, std::string const& introFileName,
    std::string const& loopingFileName, oalpp::effects::MonoEffectInterface& effect)
{
    m_logger.debug("add permanent sound with effect: " + identifier, { "jt", "audio" });
    return std::make_shared<jt::LoggingSound>(
        m_decoratee.addPermanentSound(identifier, introFileName, loopingFileName, effect),
        m_logger);
}

std::shared_ptr<jt::SoundInterface> jt::LoggingAudio::addTemporarySoundGroup(
    std::vector<std::shared_ptr<jt::SoundInterface>> const& sounds)
{
    m_logger.debug("add temporary sound group with " + std::to_string(sounds.size()) + " entries",
        { "jt", "audio" });
    return std::make_shared<jt::LoggingSound>(m_decoratee.addTemporarySoundGroup(sounds), m_logger);
}
jt::SoundFadeManager& jt::LoggingAudio::fades()
{
    m_logger.verbose("fades", { "jt", "audio" });
    return m_decoratee.fades();
}
jt::GroupVolumeSetterInterface& jt::LoggingAudio::groups()
{
    m_logger.verbose("groups", { "jt", "audio", "sound groups" });
    return m_decoratee.groups();
}
