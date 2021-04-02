#ifndef GUARD_JAMTEMPLATE_MUSICPLAYERINTERFACE_HPP_GUARD
#define GUARD_JAMTEMPLATE_MUSICPLAYERINTERFACE_HPP_GUARD

#include <string>

namespace jt {

class MusicPlayerInterface {
public:
    virtual void PlayMusic(std::string const& fileName) = 0;
    virtual void StopMusic() = 0;
    // range: 0.0f to 100.0f
    virtual void SetMusicVolume(float v) = 0;
    virtual float GetMusicVolume() = 0;
    virtual std::string GetMusicFileName() = 0;
};

} // namespace jt

#endif
