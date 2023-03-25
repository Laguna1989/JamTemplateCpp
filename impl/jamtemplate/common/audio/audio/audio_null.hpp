#ifndef JAMTEMPLATE_AUDIO_NULL_HPP
#define JAMTEMPLATE_AUDIO_NULL_HPP

#include <audio/audio/audio_interface.hpp>
#include <audio/fades/sound_fade_manager.hpp>
#include <audio/sound_groups/group_volume_manager.hpp>

namespace jt {

namespace null_objects {

class SoundContextNull : public oalpp::SoundContextInterface { };

} // namespace null_objects

class AudioNull : public AudioInterface {
public:
    void update(float elapsed) override;

    oalpp::SoundContextInterface& getContext() override;

    std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& fileName) override;
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

    std::shared_ptr<jt::SoundInterface> addTemporarySoundGroup(
        std::vector<std::shared_ptr<jt::SoundInterface>> const& sounds) override;

    SoundFadeManagerInterface& fades() override;
    GroupVolumeSetterInterface& groups() override;

private:
    null_objects::SoundContextNull m_context;

    std::unique_ptr<SoundFadeManagerInterface> m_fades { std::make_unique<SoundFadeManager>() };
    GroupVolumeManager m_groups;
};
} // namespace jt

#endif // JAMTEMPLATE_AUDIO_NULL_HPP
