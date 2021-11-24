#include "music_player.hpp"

namespace jt {

void MusicPlayer::playMusic(std::string const& fileName)
{
    m_musicFileName = fileName;
    m_music = std::make_shared<sf::Music>();
    m_music->openFromFile(fileName);
    m_music->play();
    m_music->setLoop(true);
}

void MusicPlayer::stopMusic()
{
    if (m_music) {
        m_music->stop();
    }
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
