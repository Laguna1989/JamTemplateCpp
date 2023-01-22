#include "logging_sound.hpp"
#include <audio/sound.hpp>

jt::LoggingSound::LoggingSound(
    std::shared_ptr<jt::SoundInterface> decoratee, jt::LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
    checkAndLogInvalidSampleRate();
}

jt::LoggingSound::LoggingSound(std::string const& fileName, jt::LoggerInterface& logger)
    : m_decoratee { std::make_shared<jt::Sound>(fileName) }
    , m_logger { logger }
{
    checkAndLogInvalidSampleRate();
}

void jt::LoggingSound::checkAndLogInvalidSampleRate()
{
    if (m_decoratee->getSampleRate() != 44100) {
        m_logger.error(
            "Sound is not in 44.1kHz, but in: " + std::to_string(m_decoratee->getSampleRate()));
    }
}

void jt::LoggingSound::update()
{
    m_logger.verbose("Sound update", { "jt", "audio", "sound" });
    m_decoratee->update();
}

bool jt::LoggingSound::isPlaying() const
{
    auto const isPlaying = m_decoratee->isPlaying();
    m_logger.verbose("Sound isPlaying: " + std::to_string(isPlaying), { "jt", "audio", "sound" });
    return isPlaying;
}

void jt::LoggingSound::play()
{
    m_logger.debug("Sound play", { "jt", "audio", "sound" });
    m_decoratee->play();
}

void jt::LoggingSound::stop()
{
    m_logger.debug("Sound stop", { "jt", "audio", "sound" });
    m_decoratee->stop();
}

void jt::LoggingSound::pause()
{
    m_logger.debug("Sound pause", { "jt", "audio", "sound" });
    m_decoratee->pause();
}

float jt::LoggingSound::getVolume() const
{
    auto const volume = m_decoratee->getVolume();
    m_logger.debug("Sound volume: " + std::to_string(volume), { "jt", "audio", "sound" });
    return volume;
}

void jt::LoggingSound::setVolume(float newVolume)
{
    m_logger.debug("Sound setVolume " + std::to_string(newVolume), { "jt", "audio", "sound" });
    m_decoratee->setVolume(newVolume);
}

void jt::LoggingSound::setLoop(bool doLoop)
{
    m_logger.debug("Sound setLoop " + std::to_string(doLoop), { "jt", "audio", "sound" });
    m_decoratee->setLoop(doLoop);
}

bool jt::LoggingSound::getLoop(void)
{
    auto const loop = m_decoratee->getLoop();
    m_logger.debug("Sound getLoop: " + std::to_string(loop), { "jt", "audio", "sound" });
    return loop;
}

float jt::LoggingSound::getDuration() const
{
    auto const duration = m_decoratee->getDuration();
    m_logger.debug("Sound getDuration: " + std::to_string(duration), { "jt", "audio", "sound" });
    return duration;
}

float jt::LoggingSound::getPosition() const
{
    auto const position = m_decoratee->getPosition();
    m_logger.verbose("Sound getPosition: " + std::to_string(position), { "jt", "audio", "sound" });
    return position;
}

void jt::LoggingSound::setBlend(float blend)
{
    m_logger.debug("Sound setBlend: " + std::to_string(blend), { "jt", "audio", "sound" });
    m_decoratee->setBlend(blend);
}

float jt::LoggingSound::getBlend() const
{
    auto const blend = m_decoratee->getBlend();
    m_logger.verbose("Sound getBlend: " + std::to_string(blend), { "jt", "audio", "sound" });
    return blend;
}
int jt::LoggingSound::getSampleRate() const { return m_decoratee->getSampleRate(); }

void jt::LoggingSound::setPitch(float pitch)
{
    m_logger.debug("Sound setPitch: " + std::to_string(pitch), { "jt", "audio", "sound" });
    m_decoratee->setPitch(pitch);
}
float jt::LoggingSound::getPitch() const
{
    auto const pitch = m_decoratee->getPitch();
    m_logger.verbose("Sound getPitch: " + std::to_string(pitch), { "jt", "audio", "sound" });
    return pitch;
}
void jt::LoggingSound::setVolumeProvider(jt::GroupVolumeGetterInterface& provider)
{
    m_logger.debug("SetVolumeProvider", { "jt", "audio", "sound", "volumeProvider" });
    m_decoratee->setVolumeProvider(provider);
}
void jt::LoggingSound::setVolumeGroup(std::string const& volumeGroupName)
{
    m_logger.info(
        "SetVolumeGroup: '" + volumeGroupName + "'", { "jt", "audio", "sound", "volumeGroup" });
    m_decoratee->setVolumeGroup(volumeGroupName);
}
