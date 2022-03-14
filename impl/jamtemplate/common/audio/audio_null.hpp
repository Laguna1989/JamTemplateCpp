#ifndef GUARD_JAMTEMPLATE_AUDIO_NULL_HPP
#define GUARD_JAMTEMPLATE_AUDIO_NULL_HPP

#include "audio_interface.hpp"

namespace jt {

namespace null_objects {

class SoundContextNull : public oalpp::SoundContextInterface {
};

} // namespace null_objects

class AudioNull : public AudioInterface {
public:
    void update() override;

    oalpp::SoundContextInterface& getContext() override;

    void addTemporarySound(std::weak_ptr<SoundInterface> snd) override;
    void addPermanentSound(
        std::string const& identifier, std::shared_ptr<SoundInterface> snd) override;
    std::shared_ptr<SoundInterface> soundPool(std::string const& baseIdentifier,
        std::function<std::shared_ptr<SoundInterface>()> function, std::size_t count) override;

    std::shared_ptr<SoundInterface> getPermanentSound(std::string const& identifier) override;

    void removePermanentSound(std::string const& identifier) override;

private:
    null_objects::SoundContextNull m_context;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_AUDIO_NULL_HPP
