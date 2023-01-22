#ifndef JAMTEMPLATE_LOGGING_SOUND_HPP
#define JAMTEMPLATE_LOGGING_SOUND_HPP

#include <audio/sound_interface.hpp>
#include <log/logger_interface.hpp>

namespace jt {
class LoggingSound : public SoundInterface {
public:
    /// Constructor with default decorator arguments
    LoggingSound(std::shared_ptr<SoundInterface> decoratee, LoggerInterface& logger);

    /// Constructor for convenience for creating a normal sound
    LoggingSound(std::string const& fileName, LoggerInterface& logger);

    void update() override;
    bool isPlaying() const override;

    void play() override;
    void stop() override;
    void pause() override;

    void setBlend(float blend) override;
    float getBlend() const override;

    float getVolume() const override;
    void setVolume(float newVolume) override;

    void setPitch(float pitch) override;
    float getPitch() const override;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    float getDuration() const override;
    float getPosition() const override;

    int getSampleRate() const override;
    void setVolumeProvider(GroupVolumeGetterInterface& provider) override;
    void setVolumeGroup(std::string const& volumeGroupName) override;

private:
    std::shared_ptr<SoundInterface> m_decoratee;
    LoggerInterface& m_logger;
    void checkAndLogInvalidSampleRate();
};
} // namespace jt

#endif // JAMTEMPLATE_LOGGING_SOUND_HPP
