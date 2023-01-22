#ifndef JAMTEMPLATE_SOUND_BASE_HPP
#define JAMTEMPLATE_SOUND_BASE_HPP

#include <audio/sound_interface.hpp>

namespace jt {

class SoundBase : public jt::SoundInterface {
public:
    float getVolume() const override;
    void setVolume(float newVolume) override;

    void setBlend(float blend) override;
    float getBlend() const override;

    void setVolumeProvider(GroupVolumeGetterInterface& provider) override;
    void setVolumeGroup(std::string const& volumeGroupName) override;

protected:
    float m_blend { 1.0f };
    float m_volume { 1.0f };

    std::string m_volumeGroup { "" };
    GroupVolumeGetterInterface* m_volumeProvider = nullptr;

    float getVolumeFromVolumeProvider() const;
};

} // namespace jt

#endif // JAMTEMPLATE_SOUND_BASE_HPP
