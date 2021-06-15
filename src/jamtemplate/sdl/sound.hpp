#ifndef GUARD_JAMTEMPLATE_SFML_SOUND_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_SFML_SOUND_GUARD_HPP_12345

#include "sound_base.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <memory>

namespace jt {

class Sound : public SoundBase {
private:
    std::shared_ptr<Mix_Chunk> m_wave { nullptr };
    bool m_playing { false };
    bool m_loop { false };
    int m_channel { -1 };
    float m_volume { 100.0f };

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
