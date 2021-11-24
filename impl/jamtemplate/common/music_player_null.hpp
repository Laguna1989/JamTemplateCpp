#ifndef MYAWESOMEGAME_MUSIC_PLAYER_NULL_HPP
#define MYAWESOMEGAME_MUSIC_PLAYER_NULL_HPP

#include "music_player_interface.hpp"

namespace jt {
class MusicPlayerNull : public MusicPlayerInterface {
public:
    void playMusic(std::string const& fileName) override;
    void stopMusic() override;
    void setMusicVolume(float v) override;
    float getMusicVolume() override;
    std::string getMusicFilePath() override;

private:
    std::string m_filename { "" };
    float m_volume { 100.0f };
};
} // namespace jt

#endif // MYAWESOMEGAME_MUSIC_PLAYER_NULL_HPP
