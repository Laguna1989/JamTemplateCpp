#ifndef GUARD_JAMTEMPLATE_AUDIO_IMPL_HPP
#define GUARD_JAMTEMPLATE_AUDIO_IMPL_HPP

#include "audio_interface.hpp"
#include "oalpp/sound_context.hpp"
#include <vector>

namespace jt {
class AudioImpl : public AudioInterface {
public:
    ~AudioImpl();

    std::shared_ptr<SoundInterface> createSound(std::string const& fileName) override;
    void update() override;

    void playMusic(std::string const& fileName) override;

private:
    oalpp::SoundContext m_context;

    std::vector<std::weak_ptr<SoundInterface>> m_sounds {};
    std::shared_ptr<SoundInterface> m_music { nullptr };

    void cleanUpUnusedSounds();
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_AUDIO_IMPL_HPP
