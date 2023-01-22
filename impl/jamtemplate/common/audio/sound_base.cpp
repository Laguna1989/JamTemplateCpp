#include "sound_base.hpp"
#include <stdexcept>

float jt::SoundBase::getVolume() const { return m_volume; }
void jt::SoundBase::setVolume(float newVolume) { m_volume = newVolume; }

void jt::SoundBase::setBlend(float blend)
{
    if (blend < 0.0f || blend > 1.0f) {
        throw std::invalid_argument { "Blend has to be between [0, 1]." };
    }
    m_blend = 1.0f - blend;
}
float jt::SoundBase::getBlend() const { return 1.0f - m_blend; }

void jt::SoundBase::setVolumeProvider(jt::GroupVolumeGetterInterface& provider)
{
    m_volumeProvider = &provider;
}
float jt::SoundBase::getVolumeFromVolumeProvider() const
{
    if (m_volumeProvider == nullptr) {
        return 1.0f;
    }
    return m_volumeProvider->getVolume(m_volumeGroup) * m_volumeProvider->getVolume("master");
}
void jt::SoundBase::setVolumeGroup(std::string const& volumeGroupName)
{
    m_volumeGroup = volumeGroupName;
}
