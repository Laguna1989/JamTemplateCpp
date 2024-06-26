#ifndef GUARD_JAMTEMPLATE_INTRO_LOOPING_SOUND_WITH_EFFECT_HPP
#define GUARD_JAMTEMPLATE_INTRO_LOOPING_SOUND_WITH_EFFECT_HPP

#include <audio/sound/sound_base.hpp>
#include <audio/sound/sound_with_effect.hpp>
#include <audio/sound_buffer_manager/sound_buffer_manager_interface.hpp>
#include <oalpp/effects/mono_effect_interface.hpp>
#include <oalpp/sound.hpp>
#include <oalpp/sound_data/sound_data.hpp>
#include <memory>
#include <string>

namespace jt {
class IntroLoopingSoundWithEffect : public SoundBase {
public:
    IntroLoopingSoundWithEffect(std::string const& introFileName,
        std::string const& loopingFileName, jt::SoundBufferManagerInterface& soundBufferManager,
        oalpp::effects::MonoEffectInterface& effect);
    void update() override;

    float getFinalVolume() const override;

    bool isPlaying() const override;
    void play() override;
    void stop() override;
    void pause() override;

    void setPitch(float pitch) override;
    float getPitch() const override;

    void setLoop(bool doLoop) override;
    bool getLoop(void) override;

    float getDuration() const override;
    float getPosition() const override;

    int getSampleRate() const override;
    void setVolumeProvider(jt::GroupVolumeGetterInterface& provider) override;

private:
    std::unique_ptr<jt::SoundWithEffect> m_introSound { nullptr };
    std::unique_ptr<jt::SoundWithEffect> m_loopingSound { nullptr };

    bool m_isIntroMusicPlaying { true };
    bool m_isStopped { true };
};
} // namespace jt

#endif // GUARD_JAMTEMPLATE_INTRO_LOOPING_SOUND_WITH_EFFECT_HPP
