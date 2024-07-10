#ifndef JAMTEMPLATE_AUDIO_NULL_HPP
#define JAMTEMPLATE_AUDIO_NULL_HPP

#include <audio/audio/audio_interface.hpp>

namespace jt {

namespace null_objects {

class AudioNull : public AudioInterface {
public:
    void update(float elapsed) override;

    std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& fileName) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(
        std::string const& identifier, std::string const& fileName) override;

    std::shared_ptr<jt::SoundInterface> getPermanentSound(std::string const& identifier) override;

    void setGroupVolume(std::string const& groupPath, float newVolume) override;
    float getGroupVolume(std::string const& groupPath) override;
};

} // namespace null_objects

} // namespace jt

#endif // JAMTEMPLATE_AUDIO_NULL_HPP
