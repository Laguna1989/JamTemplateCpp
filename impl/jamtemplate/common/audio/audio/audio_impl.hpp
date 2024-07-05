#ifndef JAMTEMPLATE_AUDIO_IMPL_HPP
#define JAMTEMPLATE_AUDIO_IMPL_HPP

#include <audio/audio/audio_interface.hpp>
#include <map>
#include <vector>

namespace jt {

class AudioImpl : public AudioInterface {
public:
    // TODO think about DIing FMOD context?
    AudioImpl();
    ~AudioImpl();

    void update(float elapsed) override;

    std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& fileName) override;

    std::shared_ptr<jt::SoundInterface> addPermanentSound(
        std::string const& identifier, std::string const& fileName) override;

    std::shared_ptr<jt::SoundInterface> getPermanentSound(std::string const& identifier) override;
};
} // namespace jt

#endif // JAMTEMPLATE_AUDIO_IMPL_HPP
