#include "sound.hpp"
#include <stdexcept>

namespace jt {

void Sound::doLoad(std::string const& fileName)
{
    auto const retval = m_buffer.loadFromFile(fileName);
    if (!retval) {
        throw std::invalid_argument { "cannot load sound from file " + fileName };
    }
    m_sound.setBuffer(m_buffer);
}

bool Sound::doIsPlaying() const
{
    return (m_sound.getStatus() == sf::SoundSource::Status::Playing);
}

void Sound::doPlay() { m_sound.play(); }
void Sound::doStop() { m_sound.stop(); }

float Sound::doGetVolume() const { return m_sound.getVolume(); }
void Sound::doSetVolume(float newVolume) { m_sound.setVolume(newVolume); }

void Sound::doSetLoop(bool doLoop) { m_sound.setLoop(doLoop); }
bool Sound::doGetLoop(void) { return m_sound.getLoop(); }

float Sound::doGetDuration() const { return m_buffer.getDuration().asSeconds(); }

float Sound::doGetPosition() const { return m_sound.getPlayingOffset().asSeconds(); }

} // namespace jt
