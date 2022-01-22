#ifndef GUARD_JAMTEMPLATE_AUDIO_NULL_HPP
#define GUARD_JAMTEMPLATE_AUDIO_NULL_HPP

#include "audio_interface.hpp"

namespace jt {
class AudioNull : public AudioInterface {
public:
    std::shared_ptr<SoundInterface> createSound(std::string const& fileName) override;
    void update() override;
    void playMusic(std::string const& fileName) override;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_AUDIO_NULL_HPP
