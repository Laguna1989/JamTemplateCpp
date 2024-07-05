#ifndef JAMTEMPLATE_SOUND_NULL_HPP
#define JAMTEMPLATE_SOUND_NULL_HPP

#include <audio/sound/sound_interface.hpp>

namespace jt {

class SoundNull : public SoundInterface {
public:
    bool isPlaying() const override;
    void play() override;
    void pause() override;
    void stop() override;

    float getVolume() const override;
    void setVolume(float newVolume) override;
};
} // namespace jt

#endif // JAMTEMPLATE_SOUND_NULL_HPP
