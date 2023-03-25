#ifndef JAMTEMPLATE_SOUND_FADE_MANAGER_INTERFACE_HPP
#define JAMTEMPLATE_SOUND_FADE_MANAGER_INTERFACE_HPP

#include <audio/sound/sound_interface.hpp>
#include <cstddef>
#include <memory>

namespace jt {

class SoundFadeManagerInterface {
public:
    virtual void volumeFade(std::weak_ptr<SoundInterface> sound, float durationInSeconds,
        float startVolume, float endVolume)
        = 0;

    virtual void update(float elapsed) = 0;

    virtual std::size_t size() const = 0;

    /// Destructor
    virtual ~SoundFadeManagerInterface() = default;

    // no copy, no move. Avoid slicing.
    SoundFadeManagerInterface(const SoundFadeManagerInterface&) = delete;
    SoundFadeManagerInterface(SoundFadeManagerInterface&&) = delete;
    SoundFadeManagerInterface& operator=(const SoundFadeManagerInterface&) = delete;
    SoundFadeManagerInterface& operator=(SoundFadeManagerInterface&&) = delete;

protected:
    // default default constructor can only be called from derived classes
    SoundFadeManagerInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_SOUND_FADE_MANAGER_INTERFACE_HPP
