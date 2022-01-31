#ifndef GUARD_JAMTEMPLATE_SFML_SOUND_GUARD_HPP_12345
#define GUARD_JAMTEMPLATE_SFML_SOUND_GUARD_HPP_12345

#include "oalpp/sound.hpp"
#include "oalpp/sound_context_interface.hpp"
#include "oalpp/sound_data.hpp"
#include "sound_interface.hpp"

namespace jt {

class Sound : public SoundInterface {
public:
    Sound(std::string const& fileName, oalpp::SoundContextInterface const& ctx);

    void update() override;

    bool isPlaying() const override;

    void play() override;
    void stop() override;

    float getVolume() const override;
    void setVolume(float newVolume) override;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    float getDuration() const override;

    float getPosition() const override;

    void setBlend(float blend) override;
    float getBlend() const override;

private:
    oalpp::SoundData m_buffer;
    oalpp::Sound m_sound;

    float m_blend = 0.0f;
    float m_volume = 1.0f;
};

} // namespace jt
#endif
