#ifndef GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP

#include "oalpp/sound_context/sound_context_interface.hpp"
#include "sound.hpp"
#include "sound_interface.hpp"
#include "sound_with_effect.hpp"
#include <functional>
#include <memory>
#include <string>

namespace jt {

class AudioInterface {
public:
    virtual ~AudioInterface() = default;

    // no copy, no move
    AudioInterface(const AudioInterface&) = delete;
    AudioInterface(AudioInterface&&) = delete;
    AudioInterface& operator=(const AudioInterface&) = delete;
    AudioInterface& operator=(AudioInterface&&) = delete;

    /// Update sounds in the the audio interface
    virtual void update() = 0;

    /// Add a temporary sound that will be removed once the shared pointer count is zero
    /// \param snd weak pointer to the temporary sound
    virtual void addTemporarySound(std::weak_ptr<SoundInterface> snd) = 0;
    /// Add a permanent sound that can be removed via removePermanentSound
    /// \param identifier identifier for this sound
    /// \param snd the sound to be stored
    virtual void addPermanentSound(
        std::string const& identifier, std::shared_ptr<SoundInterface> snd)
        = 0;

    virtual std::shared_ptr<SoundInterface> soundPool(std::string const& baseIdentifier,
        std::function<std::shared_ptr<SoundInterface>()> function, std::size_t count)
        = 0;

    /// Get a permanent sound
    /// \param identifier the identifier
    /// \return Shared pointer to the permanent sound (can be nullptr)
    virtual std::shared_ptr<SoundInterface> getPermanentSound(std::string const& identifier) = 0;

    /// Remove a permanent sound
    /// \param identifier the identifier of the sound to be removed
    virtual void removePermanentSound(std::string const& identifier) = 0;

    /// Get the SoundContext
    /// \return the SoundContextInterface
    virtual oalpp::SoundContextInterface& getContext() = 0;

    // TODO add group functionality
protected:
    AudioInterface() = default;
};

} // namespace jt
#endif // GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP
