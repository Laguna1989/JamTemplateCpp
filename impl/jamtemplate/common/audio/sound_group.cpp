#include "sound_group.hpp"
#include <audio/sound.hpp>
#include <random/random.hpp>
#include <algorithm>

jt::SoundGroup::SoundGroup(std::vector<std::string> const& sounds)
{
    for (auto const& f : sounds) {
        m_sounds.emplace_back(std::make_shared<jt::Sound>(f));
    }
}

void jt::SoundGroup::addSound(std::string const& fileName)
{
    m_sounds.emplace_back(std::make_shared<jt::Sound>(fileName));
}

bool jt::SoundGroup::isPlaying() const
{
    return std::any_of(
        m_sounds.cbegin(), m_sounds.cend(), [](auto const& snd) { return snd->isPlaying(); });
}

void jt::SoundGroup::play()
{
    if (m_sounds.empty()) {
        return;
    }

    std::size_t const index = Random::getInt(0, static_cast<int>(m_sounds.size()) - 1);
    m_sounds.at(index)->play();
}

void jt::SoundGroup::stop()
{
    for (auto& snd : m_sounds) {
        snd->stop();
    }
}

void jt::SoundGroup::pause()
{
    for (auto& snd : m_sounds) {
        snd->pause();
    }
}

float jt::SoundGroup::getVolume() const
{
    if (m_sounds.empty()) {
        return 0.0f;
    }
    return m_sounds.at(0)->getVolume();
}

void jt::SoundGroup::setVolume(float newVolume)
{
    for (auto& snd : m_sounds) {
        snd->setVolume(newVolume);
    }
}

void jt::SoundGroup::setLoop(bool doLoop)
{
    for (auto& snd : m_sounds) {
        snd->setLoop(doLoop);
    }
}

bool jt::SoundGroup::getLoop()
{
    if (m_sounds.empty()) {
        return false;
    }
    return m_sounds.at(0)->getLoop();
}

float jt::SoundGroup::getDuration() const { return 0.0f; }

float jt::SoundGroup::getPosition() const { return 0.0f; }
void jt::SoundGroup::update()
{
    for (auto& snd : m_sounds) {
        snd->update();
    }
}
void jt::SoundGroup::setBlend(float blend)
{
    for (auto& snd : m_sounds) {
        snd->setBlend(blend);
    }
}
float jt::SoundGroup::getBlend() const
{
    if (m_sounds.empty()) {
        return 0.0f;
    }
    return m_sounds.at(0)->getBlend();
}
void jt::SoundGroup::add(std::shared_ptr<SoundInterface> sound)
{
    if (sound != nullptr) {
        m_sounds.push_back(sound);
    }
}
int jt::SoundGroup::getSampleRate() const
{
    if (m_sounds.empty()) {
        return 0;
    }
    return m_sounds.at(0)->getSampleRate();
}

void jt::SoundGroup::setPitch(float pitch)
{
    for (auto& snd : m_sounds) {
        snd->setPitch(pitch);
    }
}
float jt::SoundGroup::getPitch() const
{
    if (m_sounds.empty()) {
        return 1.0f;
    }
    return m_sounds.at(0)->getPitch();
}
