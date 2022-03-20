#ifndef GUARD_JAMTEMPLATE_SFML_SOUND_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_SFML_SOUND_GUARD_HPP_12345

#include "counted_object.hpp"
#include "oalpp/sound.hpp"
#include "oalpp/sound_data.hpp"
#include "sound_interface.hpp"
#include <string>

namespace jt {

class Sound : public SoundInterface, public CountedObj<Sound> {
public:
    explicit Sound(std::string const& fileName);

    void update() override;

    bool isPlaying() const override;

    void play() override;
    void stop() override;
    void pause() override;

    float getVolume() const override;
    void setVolume(float newVolume) override;

    void setPitch(float pitch);
    float getPitch() const;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    float getDuration() const override;

    float getPosition() const override;

    void setBlend(float blend) override;
    float getBlend() const override;

    int getSampleRate() const override;

private:
    oalpp::SoundData m_buffer;
    oalpp::Sound m_sound;
    std::string m_fileName;

    float m_blend = 1.0f;
    float m_volume = 1.0f;
};

} // namespace jt
#endif
