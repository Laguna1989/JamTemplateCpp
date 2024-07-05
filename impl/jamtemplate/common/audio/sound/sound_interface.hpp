#ifndef JAMTEMPLATE_SOUNDINTERFACE_HPP
#define JAMTEMPLATE_SOUNDINTERFACE_HPP

namespace jt {

class SoundInterface {
public:
    /// Get isPlaying
    /// \return true if the sound is playing, false otherwise
    virtual bool isPlaying() const = 0;

    /// Play the sound
    virtual void play() = 0;
    /// Stop the sound (consecutive play will start from the beginning)
    virtual void stop() = 0;
    /// Pause the sound (consecutive play will continue where the sound was stopped)
    virtual void pause() = 0;

    // clean the sound resource
    virtual void release() { };

    /// Get Volume
    /// This is the currently stored volume that was set. It does not take SoundGroups into account.
    /// \return volume in range 0.0 to 1.0
    virtual float getVolume() const = 0;

    /// Set Volume
    /// \param newVolume in range 0.0 to 1.0
    virtual void setVolume(float newVolume) = 0;

    virtual ~SoundInterface() = default;

    // no copy, no move
    SoundInterface(SoundInterface const&) = delete;
    SoundInterface(SoundInterface&&) = delete;
    SoundInterface& operator=(SoundInterface const&) = delete;
    SoundInterface& operator=(SoundInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    SoundInterface() = default;
};
} // namespace jt

#endif // JAMTEMPLATE_SOUNDINTERFACE_HPP
