#include "sound_fade_manager.hpp"

namespace jt {

void SoundFadeManager::volumeFade(std::weak_ptr<SoundInterface> sound, float durationInSeconds,
    float startVolume, float endVolume)
{
    SoundFadeInfo info { sound, durationInSeconds, startVolume, endVolume };
    m_fades.emplace_back(info);
}

void SoundFadeManager::update(float elapsed)
{
    for (auto& fade : m_fades) {
        fade.update(elapsed);
    }
}

} // namespace jt
