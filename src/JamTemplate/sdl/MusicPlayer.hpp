#ifndef GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_INCLUDEGUARD

#include "MusicPlayerInterface.hpp"
#include <SDL2/SDL_mixer.h>

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
    std::shared_ptr<Mix_Music> m_music;
    float m_musicVolume { 0.0f };
};

} // namespace jt

#endif