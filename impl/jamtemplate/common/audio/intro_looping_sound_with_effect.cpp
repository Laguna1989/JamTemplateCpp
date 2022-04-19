#include "intro_looping_sound_with_effect.hpp"

jt::IntroLoopingSoundWithEffect::IntroLoopingSoundWithEffect(std::string const& introFileName,
    std::string const& loopingFileName, oalpp::effects::MonoEffectInterface& effect)
    : m_introDrySoundData { introFileName }
    , m_introDrySound { m_introDrySoundData }
    , m_loopingDrySoundData { loopingFileName }
    , m_loopingDrySound { m_loopingDrySoundData }

    , m_introWetSoundData { m_introDrySoundData, effect }
    , m_introWetSound { m_introWetSoundData }
    , m_loopingWetSoundData { m_loopingDrySoundData, effect }
    , m_loopingWetSound { m_loopingWetSoundData }
{
    m_loopingDrySound.setIsLooping(true);
    m_loopingWetSound.setIsLooping(true);
}

void jt::IntroLoopingSoundWithEffect::update()
{
    if (m_isStopped) {
        return;
    }

    if (m_introDrySound.isPlaying()) {
        m_introDrySound.update();
        m_introWetSound.update();
    } else {
        if (m_isIntroMusicPlaying) {
            m_isIntroMusicPlaying = false;
            m_loopingDrySound.play();
            m_loopingWetSound.play();
        }

        m_loopingDrySound.update();
        m_loopingWetSound.update();
    }

    m_introDrySound.setVolume(m_volume * (1.0f - m_blend));
    m_loopingDrySound.setVolume(m_volume * (1.0f - m_blend));
    m_introWetSound.setVolume(m_volume * (m_blend));
    m_loopingWetSound.setVolume(m_volume * (m_blend));
}

bool jt::IntroLoopingSoundWithEffect::isPlaying() const
{
    return m_introDrySound.isPlaying() || m_loopingDrySound.isPlaying();
}

void jt::IntroLoopingSoundWithEffect::play()
{
    m_isStopped = false;
    m_introDrySound.play();
    m_introWetSound.play();
}

void jt::IntroLoopingSoundWithEffect::stop()
{
    m_isIntroMusicPlaying = true;
    m_isStopped = true;

    m_introDrySound.stop();
    m_loopingDrySound.stop();
    m_introWetSound.stop();
    m_loopingWetSound.stop();
}

void jt::IntroLoopingSoundWithEffect::pause()
{
    if (m_isIntroMusicPlaying) {
        // TODO in intro this is a stop, not a pause
        m_isStopped = true;
        m_introDrySound.pause();
        m_introWetSound.pause();
    } else {
        m_loopingDrySound.pause();
        m_loopingWetSound.pause();
    }
}

float jt::IntroLoopingSoundWithEffect::getVolume() const { return m_volume; }
void jt::IntroLoopingSoundWithEffect::setVolume(float newVolume) { m_volume = newVolume; }

void jt::IntroLoopingSoundWithEffect::setPitch(float pitch)
{
    m_introDrySound.setPitch(pitch);
    m_loopingDrySound.setPitch(pitch);
    m_introWetSound.setPitch(pitch);
    m_loopingWetSound.setPitch(pitch);
}
float jt::IntroLoopingSoundWithEffect::getPitch() const { return m_introDrySound.getPitch(); }

void jt::IntroLoopingSoundWithEffect::setLoop(bool /*doLoop*/) { }
bool jt::IntroLoopingSoundWithEffect::getLoop() { return true; }

float jt::IntroLoopingSoundWithEffect::getDuration() const
{
    return m_introDrySound.getLengthInSeconds() + m_loopingDrySound.getLengthInSeconds();
}

float jt::IntroLoopingSoundWithEffect::getPosition() const
{
    if (m_introDrySound.isPlaying()) {
        return m_introDrySound.getCurrentOffsetInSeconds();
    }
    return m_introDrySound.getLengthInSeconds() + m_loopingDrySound.getCurrentOffsetInSeconds();
}

void jt::IntroLoopingSoundWithEffect::setBlend(float blend) { m_blend = blend; }
float jt::IntroLoopingSoundWithEffect::getBlend() const { return m_blend; }

int jt::IntroLoopingSoundWithEffect::getSampleRate() const
{
    return m_introDrySoundData.getSampleRate();
}
