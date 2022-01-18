#include "music_player.hpp"

namespace jt {

MusicPlayer::MusicPlayer(oalpp::SoundContext const& ctx)
    : m_ctx { ctx }
{
}

void MusicPlayer::playMusic(std::string const& fileName)
{
    m_musicFileName = fileName;

    m_buffer = oalpp::SoundData { fileName };

    m_music = std::make_shared<oalpp::Sound>(m_buffer.value(), m_ctx);
    m_music->setIsLooping(true);
    m_music->play();
}

void MusicPlayer::stopMusic()
{
    // TODO implement once oalpp supports stop
}
void MusicPlayer::setMusicVolume(float v)
{
    if (m_music) {
        m_music->setVolume(v);
    }
}

float MusicPlayer::getMusicVolume()
{
    if (m_music) {
        return m_music->getVolume();
    }
    return 0.0f;
}

std::string MusicPlayer::getMusicFilePath() { return m_musicFileName; }

} // namespace jt
