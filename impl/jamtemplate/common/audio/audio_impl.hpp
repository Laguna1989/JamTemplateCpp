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

    void addTemporarySound(std::weak_ptr<jt::SoundInterface> snd) override;
    void addPermanentSound(
        std::string const& identifier, std::shared_ptr<jt::SoundInterface> snd) override;

    std::shared_ptr<jt::SoundInterface> soundPool(std::string const& baseIdentifier,
        std::function<std::shared_ptr<jt::SoundInterface>()> function, std::size_t count) override;

    std::shared_ptr<jt::SoundInterface> getPermanentSound(std::string const& identifier) override;

    void removePermanentSound(std::string const& identifier) override;

    oalpp::SoundContextInterface& getContext() override;

private:
    oalpp::SoundContext m_context;

    std::vector<std::weak_ptr<jt::SoundInterface>> m_temporarySounds {};
    std::map<std::string, std::shared_ptr<jt::SoundInterface>> m_permanentSounds {};

    void cleanUpUnusedSounds();
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_AUDIO_IMPL_HPP
