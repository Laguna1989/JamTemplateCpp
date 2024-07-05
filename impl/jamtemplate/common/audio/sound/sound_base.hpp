#ifndef JAMTEMPLATE_SOUND_BASE_HPP
#define JAMTEMPLATE_SOUND_BASE_HPP

#include <audio/sound/sound_interface.hpp>

namespace jt {

class SoundBase : public jt::SoundInterface {
public:
    float getVolume() const override;
    void setVolume(float newVolume) override;
};

} // namespace jt

#endif // JAMTEMPLATE_SOUND_BASE_HPP
