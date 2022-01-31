#ifndef GUARD_JAMTEMPLATE_AUDIO_IMPL_HPP
#define GUARD_JAMTEMPLATE_AUDIO_IMPL_HPP

#include "audio_interface.hpp"
#include "oalpp/sound_context.hpp"
#include <map>
#include <vector>

namespace jt {
class AudioImpl : public AudioInterface {
public:
    ~AudioImpl();

    void update() override;

    void addTemporarySound(std::weak_ptr<SoundInterface> snd) override;
    void addPermanentSound(
        std::string const& identifier, std::shared_ptr<SoundInterface> snd) override;
    oalpp::SoundContextInterface& getContext() override;

    std::shared_ptr<SoundInterface> getPermanentSound(std::string const& identifier) override;

    void removePermanentSound(std::string const& identifier) override;

private:
    oalpp::SoundContext m_context;

    std::vector<std::weak_ptr<SoundInterface>> m_temporarySounds {};
    std::map<std::string, std::shared_ptr<SoundInterface>> m_permanentSounds {};

    void cleanUpUnusedSounds();
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_AUDIO_IMPL_HPP
