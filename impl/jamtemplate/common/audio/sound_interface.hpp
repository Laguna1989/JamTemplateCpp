#ifndef JAMTEMPLATE_SOUNDINTERFACE_HPP
#define JAMTEMPLATE_SOUNDINTERFACE_HPP

namespace jt {
class SoundInterface {
public:
    virtual ~SoundInterface() = default;

    virtual void update() = 0;

    virtual bool isPlaying() const = 0;

    virtual void play() = 0;
    virtual void stop() = 0;

    /// Get Volume
    /// \return volume in range 0.0 to 1.0
    virtual float getVolume() const = 0;

    /// Set Volume
    /// \param newVolume in range 0.0 to 1.0
    virtual void setVolume(float newVolume) = 0;

    virtual void setLoop(bool doLoop) = 0;
    virtual bool getLoop(void) = 0;

    virtual float getDuration() const = 0;

    virtual float getPosition() const = 0;
};
} // namespace jt

#endif // JAMTEMPLATE_SOUNDINTERFACE_HPP
