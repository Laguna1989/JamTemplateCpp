#include "logging_audio.hpp"
#include "logging_sound.hpp"
namespace jt {

LoggingAudio::LoggingAudio(AudioInterface& decoratee, LoggerInterface& logger)
    : m_decoratee { decoratee }
    , m_logger { logger }
{
}

std::shared_ptr<SoundInterface> LoggingAudio::createSound(std::string const& fileName)
{
    m_logger.debug("create sound '" + fileName + "'", { "jt", "audio" });
    return std::make_shared<LoggingSound>(m_decoratee.createSound(fileName), m_logger);
}

void LoggingAudio::update()
{
    m_logger.verbose("Audio update", { "jt", "audio" });
    m_decoratee.update();
}

void LoggingAudio::playMusic(std::string const& fileName)
{
    m_logger.debug("play music '" + fileName + "'", { "jt", "audio" });
    m_decoratee.playMusic(fileName);
}

} // namespace jt
