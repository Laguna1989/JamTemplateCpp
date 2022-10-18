#include "sound_fade_info.hpp"

jt::SoundFadeInfo::SoundFadeInfo(std::weak_ptr<jt::SoundInterface> const& sound, float duration,
    float startVolume, float endVolume)
    : m_sound(sound)
    , m_startVolume(startVolume)
    , m_endVolume(endVolume)
    , m_duration(duration)
{
}

void jt::SoundFadeInfo::update(float elapsed)
{
    m_age += elapsed;

    // TODO check if sound is still available

    auto const agePercent = m_age / m_duration; // 0-1
    auto const value = (1.0f - agePercent) * m_startVolume + agePercent * m_endVolume;
    m_sound.lock()->setVolume(value);
}
