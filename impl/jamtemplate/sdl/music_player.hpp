#ifndef GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_INCLUDEGUARD
#define GUARD_JAMTEMPLATE_MUSICPLAYER_HPP_INCLUDEGUARD

#include "music_player_interface.hpp"
#include <SDL2/SDL_mixer.h>
#include <memory>

namespace jt {

class MusicPlayer : public jt::MusicPlayerInterface {
public:
    virtual void PlayMusic(std::string const& fileName) override;
    virtual void StopMusic() override;
    // range: 0.0f to 100.0f
    virtual void SetMusicVolume(float newVolume) override;
    virtual float GetMusicVolume() override;
    virtual std::string GetMusicFilePath() override;

private:
    std::string m_musicFileName;
    std::shared_ptr<Mix_Music> m_music;
    float m_musicVolume { 0.0f };

    float JtToSdlVolume(float jtVolume) const;
};

} // namespace jt

#endif
