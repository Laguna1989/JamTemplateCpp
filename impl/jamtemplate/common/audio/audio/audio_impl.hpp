#ifndef JAMTEMPLATE_AUDIO_IMPL_HPP
#define JAMTEMPLATE_AUDIO_IMPL_HPP

#include <audio/audio/audio_interface.hpp>
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <map>
#include <vector>

namespace jt {

void checkResult(FMOD_RESULT result);

class AudioImpl : public AudioInterface {
public:
    // TODO think about DIing FMOD context?
    AudioImpl();
    ~AudioImpl();

    void update(float elapsed) override;

    std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& eventPath) override;

    std::shared_ptr<jt::SoundInterface> addPermanentSound(
        std::string const& identifier, std::string const& eventPath) override;

    std::shared_ptr<jt::SoundInterface> getPermanentSound(std::string const& identifier) override;

    void setGroupVolume(std::string const& groupPath, float newVolume) override;
    float getGroupVolume(std::string const& groupPath) override;

private:
    FMOD::Studio::System* m_studioSystem { nullptr };

    std::map<std::string, FMOD::Studio::EventInstance*> permanentSounds;
};
} // namespace jt

#endif // JAMTEMPLATE_AUDIO_IMPL_HPP
