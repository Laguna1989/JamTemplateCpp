#ifndef GUARD_JAMTEMPLATE_MUSICPLAYERINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_MUSICPLAYERINTERFACE_HPP_GUARD

#include <string>

namespace jt {

class MusicPlayerInterface {
public:
    /// Destructor
    virtual ~MusicPlayerInterface() = default;

    /// Play music
    /// \param fileName the filepath of the music (e.g. "assets/music.ogg")
    virtual void playMusic(std::string const& fileName) = 0;

    /// Stop Music
    virtual void stopMusic() = 0;

    /// Set music volume
    /// \param v the volume in range 0 to 100
    virtual void setMusicVolume(float v) = 0;

    /// Get music Volume
    /// \return the colume in range 0 to 100
    virtual float getMusicVolume() = 0;

    /// Get the music filepath
    /// \return the filepath
    virtual std::string getMusicFilePath() = 0;

    /// update the music
    virtual void update() = 0;

    const float MaxVolume { 100.0f };
};

} // namespace jt

#endif
