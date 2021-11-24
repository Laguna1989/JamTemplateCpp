#ifndef GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_GUARD
#define GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_GUARD

#include "music_player_interface.hpp"
#include <SFML/Audio.hpp>
#include <memory>

namespace jt {

class MusicPlayer : public jt::MusicPlayerInterface {
public:
    virtual void playMusic(std::string const& fileName) override;
    virtual void stopMusic() override;
    // range: 0.0f to 100.0f
    virtual void setMusicVolume(float v) override;
    virtual float getMusicVolume() override;
    virtual std::string getMusicFilePath() override;

private:
    std::string m_musicFileName;
    std::shared_ptr<sf::Music> m_music;
};

} // namespace jt
#endif
