#include "audio_null.hpp"
#include "sound_null.hpp"
namespace jt {
void AudioNull::update() { }
oalpp::SoundContextInterface& AudioNull::getContext() { return m_context; }
void AudioNull::addTemporarySound(std::weak_ptr<SoundInterface> snd) { }
void AudioNull::addPermanentSound(std::string const& identifier, std::shared_ptr<Sound> snd) { }
void AudioNull::addPermanentSoundWithEffect(
    std::string const& identifier, std::shared_ptr<SoundWithEffect> snd)
{
}

std::shared_ptr<Sound> AudioNull::getPermanentSound(std::string const& identifier)
{
    return nullptr;
}

std::shared_ptr<SoundWithEffect> AudioNull::getPermanentSoundWithEffect(
    std::string const& identifier)
{
    return nullptr;
}

void AudioNull::removePermanentSound(std::string const& identifier) { }

} // namespace jt
