#include "audio_null.hpp"
#include "sound_null.hpp"
namespace jt {
std::shared_ptr<SoundInterface> AudioNull::createSound(std::string const& fileName)
{
    return std::make_shared<SoundNull>();
}

std::shared_ptr<SoundWithEffect> AudioNull::createSoundWithEffect(
    std::string const& fileName, oalpp::effects::MonoEffectInterface& effect)
{
    return nullptr;
}

void AudioNull::update() { }

void AudioNull::playMusic(std::string const& fileName) { }

} // namespace jt
