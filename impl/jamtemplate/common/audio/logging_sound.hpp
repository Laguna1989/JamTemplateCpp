#ifndef GUARD_JAMTEMPLATE_LOGGING_SOUND_HPP
#define GUARD_JAMTEMPLATE_LOGGING_SOUND_HPP

#include "logging/logger_interface.hpp"
#include "sound_interface.hpp"

namespace jt {
class LoggingSound : public SoundInterface {
public:
    LoggingSound(std::shared_ptr<SoundInterface> decoratee, LoggerInterface& logger);
    void update() override;
    bool isPlaying() const override;
    void play() override;
    void stop() override;
    float getVolume() const override;
    void setVolume(float newVolume) override;
    void setLoop(bool doLoop) override;
    bool getLoop(void) override;
    float getDuration() const override;
    float getPosition() const override;

private:
    std::shared_ptr<SoundInterface> m_decoratee;
    LoggerInterface& m_logger;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_LOGGING_SOUND_HPP
