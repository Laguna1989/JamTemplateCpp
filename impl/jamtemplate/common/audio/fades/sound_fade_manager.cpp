#include "sound_fade_manager.hpp"
#include <algorithm>

namespace jt {

void SoundFadeManager::volumeFade(std::weak_ptr<SoundInterface> sound, float durationInSeconds,
    float startVolume, float endVolume)
{
    m_fadeInfos.emplace_back(SoundFadeInfo { sound, durationInSeconds, startVolume, endVolume });
}

void SoundFadeManager::update(float elapsed)
{
    m_fadeInfos.erase(std::remove_if(m_fadeInfos.begin(), m_fadeInfos.end(),
                          [](auto const& fadeInfo) { return !fadeInfo.hasValidSound(); }),
        m_fadeInfos.end());

    for (auto& fade : m_fadeInfos) {
        fade.update(elapsed);
    }

    m_fadeInfos.erase(std::remove_if(m_fadeInfos.begin(), m_fadeInfos.end(),
                          [](auto const& fadeInfo) { return !fadeInfo.isAlive(); }),
        m_fadeInfos.end());
}
std::size_t SoundFadeManager::size() const { return m_fadeInfos.size(); }

} // namespace jt
