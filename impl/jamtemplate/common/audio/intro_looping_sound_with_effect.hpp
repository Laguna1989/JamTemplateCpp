#ifndef GUARD_JAMTEMPLATE_INTRO_LOOPING_SOUND_WITH_EFFECT_HPP
#define GUARD_JAMTEMPLATE_INTRO_LOOPING_SOUND_WITH_EFFECT_HPP

#include <audio/sound_interface.hpp>
#include <oalpp/effects/mono_effect_interface.hpp>
#include <string>

namespace jt {
class IntroLoopingSoundWithEffect : public SoundInterface {
public:
    IntroLoopingSoundWithEffect(std::string const& introFileName,
        std::string const& loopingFileName, oalpp::effects::MonoEffectInterface& effect);
    void update() override;
    bool isPlaying() const override;
    void play() override;
    void stop() override;
    void pause() override;
    float getVolume() const override;
    void setVolume(float newVolume) override;
    void setPitch(float pitch) override;
    float getPitch() const override;
    void setLoop(bool doLoop) override;
    bool getLoop(void) override;
    float getDuration() const override;
    float getPosition() const override;
    void setBlend(float blend) override;
    float getBlend() const override;
    int getSampleRate() const override;
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_INTRO_LOOPING_SOUND_WITH_EFFECT_HPP
