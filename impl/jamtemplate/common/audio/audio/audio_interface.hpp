#ifndef JAMTEMPLATE_AUDIO_INTERFACE_HPP
#define JAMTEMPLATE_AUDIO_INTERFACE_HPP

#include <audio/sound/sound.hpp>
#include <audio/sound/sound_interface.hpp>
#include <functional>
#include <memory>
#include <string>

namespace jt {

class AudioInterface {
public:
    /// Update sounds in the audio interface
    virtual void update(float elapsed) = 0;

    // TODO(Simon) fix return value

    /// Add a temporary sound that will be removed once the shared pointer count is zero
    /// \param fileName filename of the sound to load
    /// \return shared pointer of the sound created. The user needs to keep this shared pointer
    /// alive, otherwise the sound will be deleted.
    virtual std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& fileName) = 0;

    /// Add a permanent sound that can be removed via removePermanentSound
    /// \param identifier identifier for this sound
    /// \param fileName filename of the sound to load
    virtual std::shared_ptr<jt::SoundInterface> addPermanentSound(
        std::string const& identifier, std::string const& fileName)
        = 0;

    /// Get a permanent sound
    /// \param identifier the identifier
    /// \return Shared pointer to the permanent sound (can be nullptr)
    virtual std::shared_ptr<SoundInterface> getPermanentSound(std::string const& identifier) = 0;

    /// Set the volume of a group/bus
    /// \param groupPath the path of the group
    /// \param newVolume the new volume, should be in range [0,1]
    virtual void setGroupVolume(std::string const& groupPath, float newVolume) = 0;

    /// Get the volume of a group/bus
    /// \param groupPath the path of the group
    /// \return current volume of the group, in range [0,1]
    virtual float getGroupVolume(std::string const& groupPath) = 0;

    virtual ~AudioInterface() = default;

    // no copy, no move
    AudioInterface(AudioInterface const&) = delete;
    AudioInterface(AudioInterface&&) = delete;
    AudioInterface& operator=(AudioInterface const&) = delete;
    AudioInterface& operator=(AudioInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    AudioInterface() = default;
};

} // namespace jt
#endif // JAMTEMPLATE_AUDIO_INTERFACE_HPP
