#ifndef JAMTEMPLATE_SOUND_IMPL_HPP
#define JAMTEMPLATE_SOUND_IMPL_HPP

#include <audio/sound_interface.hpp>

namespace jt {

class SoundImpl : public jt::SoundInterface {
public:
    float getVolume() const override;
    void setVolume(float newVolume) override;

    void setBlend(float blend) override;
    float getBlend() const override;

    void setVolumeProvider(GroupVolumeGetterInterface& provider) override;

protected:
    float m_blend = 1.0f;
    float m_volume = 1.0f;

    GroupVolumeGetterInterface* m_volumeProvider = nullptr;

    float getVolumeFromVolumeProvider() const;
};

} // namespace jt

#endif // JAMTEMPLATE_SOUND_IMPL_HPP
