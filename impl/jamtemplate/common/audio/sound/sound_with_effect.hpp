#ifndef JAMTEMPLATE_SOUND_WITH_EFFECT_HPP
#define JAMTEMPLATE_SOUND_WITH_EFFECT_HPP

#include <audio/sound/sound_base.hpp>
#include <audio/sound_buffer_manager/sound_buffer_manager_interface.hpp>
#include <oalpp/sound.hpp>
#include <oalpp/sound_data.hpp>

namespace jt {

class SoundWithEffect : public SoundBase {
public:
    SoundWithEffect(std::string const& fileName,
        jt::SoundBufferManagerInterface& soundBufferManager,
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

private:
    std::shared_ptr<oalpp::SoundDataInterface> m_drySoundData;
    oalpp::Sound m_drySound;

    std::shared_ptr<oalpp::SoundDataInterface> m_wetSoundData;
    oalpp::Sound m_wetSound;
};

} // namespace jt

#endif // JAMTEMPLATE_SOUND_WITH_EFFECT_HPP
