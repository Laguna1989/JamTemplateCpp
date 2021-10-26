#include "sound.hpp"
#include <iostream>
#include <stdexcept>

namespace jt {

void Sound::doLoad(std::string const& fileName)
{
    m_wave = std::shared_ptr<Mix_Chunk>(
        Mix_LoadWAV(fileName.c_str()), [](Mix_Chunk* wave) { Mix_FreeChunk(wave); });
    if (!m_wave) {
        throw std::invalid_argument { "can not load sound from file " + fileName };
    }
}

bool Sound::doIsPlaying() const { return m_playing; }

void Sound::doPlay()
{
    int loops = m_loop ? -1 : 0;
    m_channel = Mix_PlayChannel(-1, m_wave.get(), loops);
    if (m_channel == -1) {
        m_playing = false;
        std::cout << "Sound play, channel: " << std::to_string(m_channel)
                  << "\nerror: " << Mix_GetError() << std::endl;
    } else {
        m_playing = true;
    }
}

void Sound::doStop()
{
    if (m_channel != -1) {
        Mix_Pause(m_channel);
    }
    m_playing = false;
}

float Sound::doGetVolume() const { return m_volume; }
void Sound::doSetVolume(float newVolume)
{
    m_volume = newVolume;
    int v = static_cast<int>(128 * newVolume / 100.0f);
    Mix_VolumeChunk(m_wave.get(), v);
}

void Sound::doSetLoop(bool doLoop) { m_loop = doLoop; }
bool Sound::doGetLoop(void) { return m_loop; }

float Sound::doGetDuration() const { return static_cast<float>(m_wave->alen) / 176400.0f; }
float Sound::doGetPosition() const
{
    std::cout << "getPosition() not supported by web audio." << std::endl;
    return 0;
}

} // namespace jt
