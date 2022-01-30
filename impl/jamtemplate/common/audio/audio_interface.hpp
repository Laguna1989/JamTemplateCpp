#ifndef GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP

#include "oalpp/sound_context_interface.hpp"
#include "sound_interface.hpp"
#include "sound_with_effect.hpp"
#include <memory>
#include <string>

namespace jt {

class AudioInterface {
public:
    virtual ~AudioInterface() = default;
    virtual std::shared_ptr<SoundInterface> createSound(std::string const& fileName) = 0;

    virtual std::shared_ptr<SoundWithEffect> createSoundWithEffect(
        std::string const& fileName, oalpp::effects::MonoEffectInterface& effect)
        = 0;

    virtual void update() = 0;

    virtual void playMusic(std::string const& fileName) = 0;

    // TODO add group functionality
};

} // namespace jt
#endif // GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP
