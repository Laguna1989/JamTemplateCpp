#include "music_player.hpp"
#include <iostream>

namespace jt {

// will convert range from 0 - 100 to the sdl range of 0-128
float MusicPlayer::JtToSdlVolume(float jtVolume) const
{
    auto const max_sdl_volume = 128.0f;
    return max_sdl_volume * jtVolume / MaxVolume;
}

void MusicPlayer::PlayMusic(std::string const& fileName)
{
    m_musicFileName = fileName;

    m_music = std::shared_ptr<Mix_Music>(
        Mix_LoadMUS(fileName.c_str()), [](Mix_Music* m) { Mix_FreeMusic(m); });
    if (!m_music) {
        std::cout << "load audio failed\n" << Mix_GetError() << std::endl;
    }
    auto const result = Mix_PlayMusic(m_music.get(), -1);
    if (result == -1) {
        std::cout << "play music failed\n" << Mix_GetError() << std::endl;
    }
    SetMusicVolume(MaxVolume);
}
void MusicPlayer::StopMusic() { m_music = nullptr; }
// range: 0.0f to 100.0f
void MusicPlayer::SetMusicVolume(float newVolume)
{
    m_musicVolume = JtToSdlVolume(newVolume);
    Mix_VolumeMusic(static_cast<int>(m_musicVolume));
}

float MusicPlayer::GetMusicVolume() { return m_musicVolume; }
std::string MusicPlayer::GetMusicFilePath() { return m_musicFileName; }

} // namespace jt
