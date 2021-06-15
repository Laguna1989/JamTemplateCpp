#include "MusicPlayer.hpp"
#include <iostream>

namespace jt {

void MusicPlayer::PlayMusic(std::string const& fileName)
{
    m_musicFileName = fileName;

    m_music = std::shared_ptr<Mix_Music>(
        Mix_LoadMUS(fileName.c_str()), [](Mix_Music* m) { Mix_FreeMusic(m); });
    if (!m_music) {
        std::cout << "load audio failed\n" << Mix_GetError();
    }
    auto const result = Mix_PlayMusic(m_music.get(), -1);
    if (result == -1) {
        std::cout << "play music failed\n" << Mix_GetError();
    }
}
void MusicPlayer::StopMusic() { m_music = nullptr; }
// range: 0.0f to 100.0f
void MusicPlayer::SetMusicVolume(float newVolume)
{
    m_musicVolume = static_cast<int>(128 * newVolume / 100.0f);
    Mix_VolumeMusic(m_musicVolume);
}
float MusicPlayer::GetMusicVolume() { return m_musicVolume; }
std::string MusicPlayer::GetMusicFileName() { return m_musicFileName; }

} // namespace jt
