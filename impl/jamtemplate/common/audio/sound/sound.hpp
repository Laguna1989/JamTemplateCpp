#ifndef JAMTEMPLATE_SOUND_HPP
#define JAMTEMPLATE_SOUND_HPP

#include <audio/sound/sound_interface.hpp>
#include <counted_object.hpp>
#include <fmod.hpp>
#include <fmod_studio.hpp>
#include <string>

namespace jt {

class Sound : public SoundInterface, public CountedObj<Sound> {
public:
    Sound(FMOD::Studio::EventInstance* instance);

    bool isPlaying() const override;

    void play() override;
    void stop() override;
    void pause() override;
    void release() override;

    float getVolume() const override;
    void setVolume(float newVolume) override;

    bool checkValid() const;

private:
    FMOD::Studio::EventInstance* m_instance;
};

} // namespace jt
#endif // JAMTEMPLATE_SOUND_HPP
