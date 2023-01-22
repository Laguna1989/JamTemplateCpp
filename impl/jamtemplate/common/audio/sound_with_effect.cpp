#include "sound_with_effect.hpp"

jt::SoundWithEffect::SoundWithEffect(
    std::string const& fileName, oalpp::effects::MonoEffectInterface& effect)
    : m_drySoundData { fileName }
    , m_drySound { m_drySoundData }
    , m_wetSoundData { m_drySoundData, effect }
    , m_wetSound { m_wetSoundData }
{
}

void jt::SoundWithEffect::update()
{
    m_drySound.setVolume(m_volume * (1.0f - m_blend) * getVolumeFromVolumeProvider());
    m_wetSound.setVolume(m_volume * m_blend * getVolumeFromVolumeProvider());

    m_drySound.update();
    m_wetSound.update();
}

bool jt::SoundWithEffect::isPlaying() const { return m_drySound.isPlaying(); }
void jt::SoundWithEffect::play()
{
    m_drySound.play();
    m_wetSound.play();
}

void jt::SoundWithEffect::stop()
{
    m_drySound.stop();
    m_wetSound.stop();
}

void jt::SoundWithEffect::pause()
{
    m_drySound.pause();
    m_wetSound.pause();
}

void jt::SoundWithEffect::setLoop(bool doLoop)
{
    m_drySound.setIsLooping(doLoop);
    m_wetSound.setIsLooping(doLoop);
}

void jt::SoundWithEffect::setPitch(float pitch)
{
    m_drySound.setPitch(pitch);
    m_wetSound.setPitch(pitch);
}

float jt::SoundWithEffect::getPitch() const { return m_drySound.getPitch(); }

bool jt::SoundWithEffect::getLoop(void) { return m_drySound.getIsLooping(); }
float jt::SoundWithEffect::getDuration() const { return m_drySound.getLengthInSeconds(); }

float jt::SoundWithEffect::getPosition() const { return m_drySound.getCurrentOffsetInSeconds(); }

int jt::SoundWithEffect::getSampleRate() const { return m_drySoundData.getSampleRate(); }
