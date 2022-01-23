#include "logging_sound_decorator.hpp"

namespace jt {

LoggingSoundDecorator::LoggingSoundDecorator(
    std::shared_ptr<SoundInterface> decoratee, LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

void LoggingSoundDecorator::update()
{
    m_logger.verbose("Sound update", { "jt", "audio", "sound" });
    m_decoratee->update();
}

bool LoggingSoundDecorator::isPlaying() const
{
    auto const isPlaying = m_decoratee->isPlaying();
    m_logger.verbose("Sound isPlaying: " + std::to_string(isPlaying), { "jt", "audio", "sound" });
    return isPlaying;
}

void LoggingSoundDecorator::play()
{
    m_logger.debug("Sound play", { "jt", "audio", "sound" });
    m_decoratee->play();
}

void LoggingSoundDecorator::stop()
{
    m_logger.debug("Sound stop", { "jt", "audio", "sound" });
    m_decoratee->stop();
}

float LoggingSoundDecorator::getVolume() const
{
    auto const volume = m_decoratee->getVolume();
    m_logger.debug("Sound volume: " + std::to_string(volume), { "jt", "audio", "sound" });
    return volume;
}

void LoggingSoundDecorator::setVolume(float newVolume)
{
    m_logger.debug("Sound setVolume " + std::to_string(newVolume), { "jt", "audio", "sound" });
    m_decoratee->setVolume(newVolume);
}

void LoggingSoundDecorator::setLoop(bool doLoop)
{
    m_logger.debug("Sound setLoop " + std::to_string(doLoop), { "jt", "audio", "sound" });
    m_decoratee->setLoop(doLoop);
}

bool LoggingSoundDecorator::getLoop(void)
{
    auto const loop = m_decoratee->getLoop();
    m_logger.debug("Sound getLoop: " + std::to_string(loop), { "jt", "audio", "sound" });
    return loop;
}

float LoggingSoundDecorator::getDuration() const
{
    auto const duration = m_decoratee->getDuration();
    m_logger.debug("Sound getDuration: " + std::to_string(duration), { "jt", "audio", "sound" });
    return duration;
}

float LoggingSoundDecorator::getPosition() const
{
    auto const position = m_decoratee->getPosition();
    m_logger.verbose("Sound getPosition: " + std::to_string(position), { "jt", "audio", "sound" });
    return position;
}

} // namespace jt
