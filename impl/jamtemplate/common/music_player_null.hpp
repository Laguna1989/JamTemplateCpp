#ifndef MYAWESOMEGAME_MUSIC_PLAYER_NULL_HPP
#define MYAWESOMEGAME_MUSIC_PLAYER_NULL_HPP

#include "music_player_interface.hpp"

namespace jt {
class MusicPlayerNull : public MusicPlayerInterface {
public:
    void PlayMusic(std::string const& fileName) override;
    void StopMusic() override;
    void SetMusicVolume(float v) override;
    float GetMusicVolume() override;
    std::string GetMusicFilePath() override;

private:
    std::string m_filename { "" };
    float m_volume { 100.0f };
};
} // namespace jt

#endif // MYAWESOMEGAME_MUSIC_PLAYER_NULL_HPP
