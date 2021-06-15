#ifndef GUARD_JAMTEMPLATE_SOUND_BASE_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_SOUND_BASE_GUARD_HPP_12345

#include <stdexcept>
#include <string>

namespace jt {

class SoundBase {
public:
    virtual ~SoundBase() = default;

    void load(std::string const& fileName)
    {
        doLoad(fileName);
        m_isInitialized = true;
    }

    bool isInitialized() const { return m_isInitialized; }

    void play()
    {
        checkInitialized("Can not call play() of uninitialized sound. Call load().");
        doPlay();
    }
    bool isPlaying() const
    {
        checkInitialized("Can not call isPlaying() of uninitialized sound. Call load()!");
        return doIsPlaying();
    }

    // returns the volume of the sound in the range [0, 100]
    float getVolume() const
    {
        checkInitialized("Can not call getVolume() of uninitialized sound. Call load()!");
        return doGetVolume();
    }

    // set the volume of the sound in the range [0, 100]
    void setVolume(float newVolume)
    {
        checkInitialized("Can not call setVolume() of uninitialized sound. Call load()!");
        if (newVolume < 0.0f || newVolume > 100.0f) {
            throw std::invalid_argument { "volume " + std::to_string(newVolume)
                + " is not allowd. Volume has to be in range [0,100]." };
        }
        doSetVolume(newVolume);
    }

    void stop()
    {
        checkInitialized("Can not call stop() of uninitialized sound. Call load()!");
        doStop();
    }

    void setLoop(bool doLoop)
    {
        checkInitialized("Can not call setLoop() of uninitialied sound. Call load()!");
        doSetLoop(doLoop);
    }

    bool getLoop()
    {
        checkInitialized("Can not call getLoop() of uninitialied sound. Call load()!");
        return doGetLoop();
    }

    // returns the length of the sound in seconds
    float getDuration() const
    {
        checkInitialized("Can not call getDuration() of uninitialied sound. Call load()!");
        return doGetDuration();
    }

    // returns the current playing position of the sound in seconds
    float getPosition() const
    {
        checkInitialized("Can not call getDuration() of uninitialied sound. Call load()!");
        return doGetPosition();
    }

protected:
    void checkInitialized(std::string const& error) const
    {
        if (!isInitialized()) {
            throw std::logic_error { error.c_str() };
        }
    }

protected:
    bool m_isInitialized { false };

private:
    virtual void doLoad(std::string const& fileName) = 0;
    virtual bool doIsPlaying() const = 0;

    virtual void doPlay() = 0;
    virtual void doStop() = 0;

    virtual float doGetVolume() const = 0;
    virtual void doSetVolume(float newVolume) = 0;

    virtual void doSetLoop(bool doLoop) = 0;
    virtual bool doGetLoop(void) = 0;

    virtual float doGetDuration() const = 0;

    virtual float doGetPosition() const = 0;
}; // namespace jt

} // namespace jt

#endif
