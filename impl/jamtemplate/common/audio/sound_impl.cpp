#include "sound_impl.hpp"
#include <stdexcept>

float jt::SoundImpl::getVolume() const { return m_volume; }
void jt::SoundImpl::setVolume(float newVolume) { m_volume = newVolume; }

void jt::SoundImpl::setBlend(float blend)
{
    if (blend < 0.0f || blend > 1.0f) {
        throw std::invalid_argument { "Blend has to be between [0, 1]." };
    }
    m_blend = 1.0f - blend;
}
float jt::SoundImpl::getBlend() const { return 1.0f - m_blend; }

void jt::SoundImpl::setVolumeProvider(jt::GroupVolumeGetterInterface& provider)
{
    m_volumeProvider = &provider;
}
float jt::SoundImpl::getVolumeFromVolumeProvider() const
{
    if (m_volumeProvider == nullptr) {
        return 1.0f;
    }
    return m_volumeProvider->getVolume("");
}
