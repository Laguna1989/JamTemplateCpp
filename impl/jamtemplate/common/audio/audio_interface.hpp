#ifndef GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP

#include "oalpp/sound_context_interface.hpp"
#include "sound.hpp"
#include "sound_interface.hpp"
#include "sound_with_effect.hpp"
#include <memory>
#include <string>

namespace jt {

class AudioInterface {
public:
    virtual ~AudioInterface() = default;

    virtual void update() = 0;

    virtual void addTemporarySound(std::weak_ptr<SoundInterface> snd) = 0;
    virtual void addPermanentSound(
        std::string const& identifier, std::shared_ptr<SoundInterface> snd)
        = 0;

    virtual std::shared_ptr<SoundInterface> getPermanentSound(std::string const& identifier) = 0;

    virtual void removePermanentSound(std::string const& identifier) = 0;

    virtual oalpp::SoundContextInterface& getContext() = 0;

    // TODO add group functionality
};

} // namespace jt
#endif // GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP
