#include "audio_null.hpp"
#include "sound_null.hpp"
namespace jt {
std::shared_ptr<SoundInterface> AudioNull::createSound(std::string const& fileName)
{
    return std::make_shared<SoundNull>();
}
void AudioNull::update() { }

void AudioNull::playMusic(std::string const& fileName) { }
} // namespace jt
