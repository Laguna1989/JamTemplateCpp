#ifndef JAMTEMPLATE_FADE_MANAGER_HPP
#define JAMTEMPLATE_FADE_MANAGER_HPP

#include <audio/sound_fade_info.hpp>
#include <audio/sound_interface.hpp>
#include <cstddef>
#include <memory>
#include <vector>

namespace jt {

// TODO This class should implement an interface.
class SoundFadeManager {
public:
    void volumeFade(std::weak_ptr<SoundInterface> sound, float durationInSeconds, float startVolume,
        float endVolume);

    void update(float fadeInfo);

    std::size_t size() const;

private:
    std::vector<SoundFadeInfo> m_fadeInfos {};
};

} // namespace jt

#endif // JAMTEMPLATE_FADE_MANAGER_HPP
