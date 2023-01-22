#include "intro_looping_sound_with_effect.hpp"

jt::IntroLoopingSoundWithEffect::IntroLoopingSoundWithEffect(std::string const& introFileName,
    std::string const& loopingFileName, oalpp::effects::MonoEffectInterface& effect)
    : m_introSound { std::make_unique<jt::SoundWithEffect>(introFileName, effect) }
    , m_loopingSound { std::make_unique<jt::SoundWithEffect>(loopingFileName, effect) }
{
    m_loopingSound->setLoop(true);
}

void jt::IntroLoopingSoundWithEffect::update()
{
    if (m_isStopped) {
        return;
    }

    if (m_introSound->isPlaying()) {
        m_introSound->update();
    } else {
        if (m_isIntroMusicPlaying) {
            m_isIntroMusicPlaying = false;
            m_loopingSound->play();
        }

        m_loopingSound->update();
    }

    m_introSound->setVolume(m_volume);
    m_loopingSound->setVolume(m_volume);
    m_introSound->setBlend(m_blend);
    m_loopingSound->setBlend(m_blend);
}

bool jt::IntroLoopingSoundWithEffect::isPlaying() const
{
    return m_introSound->isPlaying() || m_loopingSound->isPlaying();
}

void jt::IntroLoopingSoundWithEffect::play()
{
    m_isStopped = false;
    m_introSound->play();
}

void jt::IntroLoopingSoundWithEffect::stop()
{
    m_isIntroMusicPlaying = true;
    m_isStopped = true;

    m_introSound->stop();
    m_loopingSound->stop();
}

void jt::IntroLoopingSoundWithEffect::pause()
{
    if (m_isIntroMusicPlaying) {
        // TODO in intro this is a stop, not a pause
        m_isStopped = true;
        m_introSound->pause();
    } else {
        m_loopingSound->pause();
    }
}

void jt::IntroLoopingSoundWithEffect::setPitch(float pitch)
{
    m_introSound->setPitch(pitch);
    m_loopingSound->setPitch(pitch);
}
float jt::IntroLoopingSoundWithEffect::getPitch() const { return m_introSound->getPitch(); }

void jt::IntroLoopingSoundWithEffect::setLoop(bool /*doLoop*/) { }
bool jt::IntroLoopingSoundWithEffect::getLoop() { return true; }

float jt::IntroLoopingSoundWithEffect::getDuration() const
{
    return m_introSound->getDuration() + m_loopingSound->getDuration();
}

float jt::IntroLoopingSoundWithEffect::getPosition() const
{
    if (m_introSound->isPlaying()) {
        return m_introSound->getPosition();
    }
    return m_introSound->getPosition() + m_loopingSound->getPosition();
}

int jt::IntroLoopingSoundWithEffect::getSampleRate() const { return m_introSound->getSampleRate(); }
void jt::IntroLoopingSoundWithEffect::setVolumeProvider(jt::GroupVolumeGetterInterface& provider) {
}
