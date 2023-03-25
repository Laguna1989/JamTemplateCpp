#ifndef JAMTEMPLATE_AUDIO_IMPL_HPP
#define JAMTEMPLATE_AUDIO_IMPL_HPP

#include <audio/audio/audio_interface.hpp>
#include <audio/fades/sound_fade_manager.hpp>
#include <audio/sound_groups/group_volume_manager.hpp>
#include <oalpp/sound_context.hpp>
#include <map>
#include <vector>

namespace jt {
class AudioImpl : public AudioInterface {
public:
    AudioImpl(std::unique_ptr<SoundFadeManagerInterface> soundFadeManager = nullptr);
    ~AudioImpl();

    void update(float elapsed) override;

    std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& fileName) override;
    std::shared_ptr<jt::SoundInterface> addTemporarySoundGroup(
        std::vector<std::shared_ptr<jt::SoundInterface>> const& sounds) override;

    std::shared_ptr<jt::SoundInterface> addPermanentSound(
        std::string const& identifier, std::string const& fileName) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& fileName, oalpp::effects::MonoEffectInterface& effect) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& introFileName, std::string const& loopingFileName,
        oalpp::effects::MonoEffectInterface& effect) override;

    std::shared_ptr<jt::SoundInterface> soundPool(
        std::string const& baseIdentifier, std::string const& fileName, std::size_t count) override;

    std::shared_ptr<jt::SoundInterface> getPermanentSound(std::string const& identifier) override;

    void removePermanentSound(std::string const& identifier) override;

    oalpp::SoundContextInterface& getContext() override;

    SoundFadeManagerInterface& fades() override;

    GroupVolumeSetterInterface& groups() override;

private:
    oalpp::SoundContext m_context;

    std::vector<std::weak_ptr<jt::SoundInterface>> m_temporarySounds {};
    std::map<std::string, std::shared_ptr<jt::SoundInterface>> m_permanentSounds {};

    std::unique_ptr<SoundFadeManagerInterface> m_fades;

    GroupVolumeManager m_volumeGroups;

    void cleanUpUnusedSounds();
};
} // namespace jt

#endif // JAMTEMPLATE_AUDIO_IMPL_HPP
