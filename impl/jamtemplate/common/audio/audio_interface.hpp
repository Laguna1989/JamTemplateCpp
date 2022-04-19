#ifndef JAMTEMPLATE_AUDIO_INTERFACE_HPP
#define JAMTEMPLATE_AUDIO_INTERFACE_HPP

#include <audio/sound.hpp>
#include <audio/sound_interface.hpp>
#include <audio/sound_with_effect.hpp>
#include <oalpp/sound_context/sound_context_interface.hpp>
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

    /// Add a permanent sound that can be removed via removePermanentSound
    /// \param identifier identifier for this sound
    /// \param fileName filename of the sound to load
    /// \param effect effect to be used on the sound
    /// \return shared pointer to the Sound
    virtual std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& fileName, oalpp::effects::MonoEffectInterface& effect)
        = 0;

    /// Add a permanent sound that can be removed via removePermanentSound
    /// \param identifier identifier for this sound
    /// \param introFileName filename of the intro sound to load
    /// \param loopingFileName filename of the sound to be looped
    /// \param effect effect to be used on the sound
    /// \return shared pointer to the Sound
    virtual std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& introFileName, std::string const& loopingFileName,
        oalpp::effects::MonoEffectInterface& effect)
        = 0;

    virtual std::shared_ptr<SoundInterface> soundPool(
        std::string const& baseIdentifier, std::string const& fileName, std::size_t count)
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
#endif // JAMTEMPLATE_AUDIO_INTERFACE_HPP
