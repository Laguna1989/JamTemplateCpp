#include "logging_audio_decorator.hpp"
#include "logging_sound_decorator.hpp"
namespace jt {

LoggingAudioDecorator::LoggingAudioDecorator(AudioInterface& decoratee, LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

std::shared_ptr<SoundInterface> LoggingAudioDecorator::createSound(std::string const& fileName)
{
    m_logger.debug("create sound '" + fileName + "'", { "jt", "audio" });
    return std::make_shared<LoggingSoundDecorator>(m_decoratee.createSound(fileName), m_logger);
}

void LoggingAudioDecorator::update()
{
    m_logger.verbose("Audio update", { "jt", "audio" });
    m_decoratee.update();
}

void LoggingAudioDecorator::playMusic(std::string const& fileName)
{
    m_logger.debug("play music '" + fileName + "'", { "jt", "audio" });
    m_decoratee.playMusic(fileName);
}

} // namespace jt
