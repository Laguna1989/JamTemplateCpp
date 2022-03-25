#ifndef JAMTEMPLATE_SOUNDINTERFACE_HPP
#define JAMTEMPLATE_SOUNDINTERFACE_HPP

namespace jt {

class SoundInterface {
public:
    virtual ~SoundInterface() = default;

    // no copy, no move
    SoundInterface(const SoundInterface&) = delete;
    SoundInterface(SoundInterface&&) = delete;
    SoundInterface& operator=(const SoundInterface&) = delete;
    SoundInterface& operator=(SoundInterface&&) = delete;

    /// Update the sound
    virtual void update() = 0;

    /// Get isPlaying
    /// \return true if is playing, false otherwise
    virtual bool isPlaying() const = 0;

    /// Play the sound
    virtual void play() = 0;
    /// Stop the sound (consecutive play will start from the beginning)
    virtual void stop() = 0;
    /// Pause the sound (consecutive play will continue where the sound was stopped)
    virtual void pause() = 0;

    /// Get Volume
    /// \return volume in range 0.0 to 1.0
    virtual float getVolume() const = 0;

    /// Set Volume
    /// \param newVolume in range 0.0 to 1.0
    virtual void setVolume(float newVolume) = 0;

    /// Set Pitch
    /// \param pitch new pitch value
    virtual void setPitch(float pitch) = 0;
    /// Get pitch
    /// \return pitch value
    virtual float getPitch() const = 0;

    /// Set Loop
    /// \param doLoop true if sound should loop, false otherwise
    virtual void setLoop(bool doLoop) = 0;
    /// Get Loop
    /// \return true if sound is looping, false otherwise
    virtual bool getLoop(void) = 0;

    /// Get Sound duration
    /// \return duration in seconds
    virtual float getDuration() const = 0;

    /// Get Position
    /// \return the current playing position in seconds
    virtual float getPosition() const = 0;

    /// Set blend
    /// \param blend blend parameter (between 0 and 1)
    virtual void setBlend(float blend) = 0;

    /// Get blend
    /// \return blend Parameter (between 0 and 1)
    virtual float getBlend() const = 0;

    /// Get sample rate
    /// \return the sample rate in Hz
    virtual int getSampleRate() const = 0;

protected:
    SoundInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_SOUNDINTERFACE_HPP
