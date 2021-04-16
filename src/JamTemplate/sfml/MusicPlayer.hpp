﻿#ifndef GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_GUARD
#define GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_GUARD

#include "MusicPlayerInterface.hpp"
#include <SFML/Audio.hpp>
#include <memory>

namespace jt {

class MusicPlayer : public jt::MusicPlayerInterface {
    virtual void PlayMusic(std::string const& fileName) override;
    virtual void StopMusic() override;
    // range: 0.0f to 100.0f
    virtual void SetMusicVolume(float v) override;
    virtual float GetMusicVolume() override;
    virtual std::string GetMusicFileName() override;

private:
    std::string m_musicFileName;
    std::shared_ptr<sf::Music> m_music;
};

} // namespace jt
#endif
