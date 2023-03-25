#ifndef JAMTEMPLATE_FADE_MANAGER_HPP
#define JAMTEMPLATE_FADE_MANAGER_HPP

#include <audio/fades/sound_fade_info.hpp>
#include <audio/fades/sound_fade_manager_interface.hpp>
#include <vector>

namespace jt {

// TODO This class should implement an interface.
class SoundFadeManager : public jt::SoundFadeManagerInterface {
public:
    void volumeFade(std::weak_ptr<SoundInterface> sound, float durationInSeconds, float startVolume,
        float endVolume) override;

    void update(float elapsed) override;

    std::size_t size() const override;

private:
    std::vector<SoundFadeInfo> m_fadeInfos {};
};

} // namespace jt

#endif // JAMTEMPLATE_FADE_MANAGER_HPP
