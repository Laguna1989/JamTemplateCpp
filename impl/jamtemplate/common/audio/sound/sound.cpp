#include "sound.hpp"
#include "audio/audio/audio_impl.hpp"
#include <iostream>

jt::Sound::Sound(FMOD::Studio::EventInstance* instance)
    : m_instance { instance }
{
    checkValid();
}

bool jt::Sound::isPlaying() const
{
    if (!checkValid())
        return false;

    FMOD_STUDIO_PLAYBACK_STATE state;
    jt::checkResult(m_instance->getPlaybackState(&state));

    return state == FMOD_STUDIO_PLAYBACK_PLAYING || state == FMOD_STUDIO_PLAYBACK_STARTING;
}

void jt::Sound::play()
{
    if (!checkValid())
        return;

    jt::checkResult(m_instance->start());

    release();
}

void jt::Sound::stop()
{
    if (!checkValid())
        return;

    jt::checkResult(m_instance->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
}

void jt::Sound::pause()
{
    if (checkValid())
        m_instance->setPaused(true);
}

float jt::Sound::getVolume() const
{
    if (!checkValid())
        return 0.0f;

    float volume { 0.0f };
    float finalVolume { 0.0f };
    jt::checkResult(m_instance->getVolume(&volume, &finalVolume));

    return volume;
}

void jt::Sound::setVolume(float newVolume)
{
    if (!checkValid())
        return;

    jt::checkResult(m_instance->setVolume(newVolume));
}

bool jt::Sound::checkValid() const
{
    if (m_instance == nullptr) {
        std::cerr << "created sound with nullptr" << std::endl;
        return false;
    }
    if (!m_instance->isValid()) {
        std::cerr << "Sound with invalid instance" << std::endl;
        return false;
    }

    return true;
}

void jt::Sound::release()
{
    if (!checkValid())
        return;
    checkResult(m_instance->release());
}
