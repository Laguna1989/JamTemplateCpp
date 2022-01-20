#ifndef GUARD_JAMTEMPLATE_SOUND_NULL_HPP
#define GUARD_JAMTEMPLATE_SOUND_NULL_HPP

#include "sound_interface.hpp"

namespace jt {

class SoundNull : public SoundInterface {
public:
    void update() override;
    bool isPlaying() const override;
    void play() override;
    void stop() override;
    float getVolume() const override;
    void setVolume(float newVolume) override;
    void setLoop(bool doLoop) override;
    bool getLoop(void) override;
    float getDuration() const override;
    float getPosition() const override;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_SOUND_NULL_HPP
