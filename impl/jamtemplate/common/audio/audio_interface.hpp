#ifndef GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP
#define GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP

#include "sound_interface.hpp"
#include <memory>
#include <string>

namespace jt {

class AudioInterface {
public:
    virtual ~AudioInterface() = default;
    virtual std::shared_ptr<SoundInterface> createSound(std::string const& fileName) = 0;

    virtual void update() = 0;

    virtual void playMusic(std::string const& fileName) = 0;

    // TODO add group functionality
};

} // namespace jt
#endif // GUARD_JAMTEMPLATE_AUDIO_INTERFACE_HPP
