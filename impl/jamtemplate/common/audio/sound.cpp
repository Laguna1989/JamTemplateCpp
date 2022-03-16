#include "sound.hpp"
#include <stdexcept>

namespace jt {

Sound::Sound(std::string const& fileName)
    : m_buffer { fileName }
    , m_sound { m_buffer }
    , m_fileName { fileName }
{
}

void Sound::update()
{
    m_sound.update();
    m_sound.setVolume(m_blend * m_volume);
}

bool Sound::isPlaying() const { return m_sound.isPlaying(); }

void Sound::play() { m_sound.play(); }
void Sound::stop() { m_sound.stop(); }
void Sound::pause() { m_sound.pause(); }

float Sound::getVolume() const { return m_volume; }
void Sound::setVolume(float newVolume) { m_volume = newVolume; }

void Sound::setLoop(bool doLoop) { m_sound.setIsLooping(doLoop); }
bool Sound::getLoop(void) { return m_sound.getIsLooping(); }

float Sound::getDuration() const { return m_sound.getLengthInSeconds(); }

float Sound::getPosition() const { return m_sound.getCurrentOffsetInSeconds(); }
void Sound::setBlend(float blend) { m_blend = 1.0f - blend; }
float Sound::getBlend() const { return 1.0f - m_blend; }

void Sound::setPitch(float pitch) { m_sound.setPitch(pitch); }
float Sound::getPitch() const { return m_sound.getPitch(); }
int Sound::getSampleRate() const { return m_buffer.getSampleRate(); }

} // namespace jt
