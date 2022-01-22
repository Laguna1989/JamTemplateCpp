#include "sound.hpp"
#include <stdexcept>

namespace jt {

Sound::Sound(std::string const& fileName, oalpp::SoundContext const& ctx)
    : m_buffer { fileName }
    , m_sound { m_buffer, ctx }
{
}

void Sound::update() { m_sound.update(); }

bool Sound::isPlaying() const { return m_sound.isPlaying(); }

void Sound::play() { m_sound.play(); }
void Sound::stop() { m_sound.stop(); }

float Sound::getVolume() const { return m_sound.getVolume(); }
void Sound::setVolume(float newVolume) { m_sound.setVolume(newVolume); }

void Sound::setLoop(bool doLoop) { m_sound.setIsLooping(doLoop); }
bool Sound::getLoop(void) { return m_sound.getIsLooping(); }

float Sound::getDuration() const { return m_sound.getLengthInSeconds(); }

float Sound::getPosition() const { return m_sound.getCurrentPositionInSeconds(); }

} // namespace jt
