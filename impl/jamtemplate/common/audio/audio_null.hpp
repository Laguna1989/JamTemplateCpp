#ifndef JAMTEMPLATE_AUDIO_NULL_HPP
#define JAMTEMPLATE_AUDIO_NULL_HPP

#include <audio/audio_interface.hpp>

namespace jt {

namespace null_objects {

class SoundContextNull : public oalpp::SoundContextInterface {
};

} // namespace null_objects

class AudioNull : public AudioInterface {
public:
    void update() override;

    oalpp::SoundContextInterface& getContext() override;

    std::shared_ptr<jt::SoundInterface> addTemporarySound(std::string const& fileName) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(
        std::string const& identifier, std::string const& fileName) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& fileName, oalpp::effects::MonoEffectInterface& effect) override;
    std::shared_ptr<jt::SoundInterface> addPermanentSound(std::string const& identifier,
        std::string const& introFileName, std::string const& loopingFileName,
        oalpp::effects::MonoEffectInterface& effect) override;

    std::shared_ptr<SoundInterface> soundPool(
        std::string const& baseIdentifier, std::string const& fileName, std::size_t count) override;

    std::shared_ptr<SoundInterface> getPermanentSound(std::string const& identifier) override;

    void removePermanentSound(std::string const& identifier) override;

private:
    null_objects::SoundContextNull m_context;
};
} // namespace jt

#endif // JAMTEMPLATE_AUDIO_NULL_HPP
