#include "sound_with_effect.hpp"

namespace jt {

SoundWithEffect::SoundWithEffect(
    std::string const& fileName, oalpp::effects::MonoEffectInterface& effect)
    : m_drySoundData { fileName }
    , m_drySound { m_drySoundData }
    , m_wetSoundData { m_drySoundData, effect }
    , m_wetSound { m_wetSoundData }
{
}

void SoundWithEffect::update()
{
    m_drySound.update();
    m_wetSound.update();

    m_drySound.setVolume(m_volume * (1.0f - m_blend));
    m_wetSound.setVolume(m_volume * (m_blend));
}
bool SoundWithEffect::isPlaying() const { return m_drySound.isPlaying(); }
void SoundWithEffect::play()
{
    m_drySound.play();
    m_wetSound.play();
}

void SoundWithEffect::stop()
{
    m_drySound.stop();
    m_wetSound.stop();
}
void SoundWithEffect::pause()
{
    m_drySound.pause();
    m_wetSound.pause();
}

float SoundWithEffect::getVolume() const { return m_volume; }

void SoundWithEffect::setVolume(float newVolume) { m_volume = newVolume; }
void SoundWithEffect::setLoop(bool doLoop)
{
    m_drySound.setIsLooping(doLoop);
    m_wetSound.setIsLooping(doLoop);
}

bool SoundWithEffect::getLoop(void) { return m_drySound.getIsLooping(); }

float SoundWithEffect::getDuration() const { return m_drySound.getLengthInSeconds(); }

float SoundWithEffect::getPosition() const { return m_drySound.getCurrentOffsetInSeconds(); }
float SoundWithEffect::getBlend() const { return m_blend; }
void SoundWithEffect::setBlend(float blend) { m_blend = blend; }

} // namespace jt
