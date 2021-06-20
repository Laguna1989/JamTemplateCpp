#ifndef GUARD_JAMTEMPLATE_SFML_SOUND_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_SFML_SOUND_GUARD_HPP_12345

#include "SFML/Audio.hpp"
#include "sound_base.hpp"

namespace jt {

class Sound : public SoundBase {
private:
    sf::SoundBuffer m_buffer;
    sf::Sound m_sound;

    void doLoad(std::string const& fileName) override;
    bool doIsPlaying() const override;

    void doPlay() override;
    void doStop() override;

    float doGetVolume() const override;
    void doSetVolume(float newVolume) override;

    void doSetLoop(bool doLoop) override;
    bool doGetLoop(void) override;

    float doGetDuration() const override;

    float doGetPosition() const override;
};

} // namespace jt
#endif
