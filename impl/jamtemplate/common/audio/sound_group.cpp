#include "sound_group.hpp"
#include "random/random.hpp"
#include "sound.hpp"
#include <algorithm>


jt::SoundGroup::SoundGroup(std::vector<std::string> const& sounds, oalpp::SoundContext const& ctx)
{
    for (auto const& f : sounds) {
        m_sounds.emplace_back(std::make_shared<jt::Sound>(f, ctx));
    }
}

void jt::SoundGroup::addSound(std::string const& fileName, oalpp::SoundContext const& ctx)
{
    m_sounds.emplace_back(std::make_shared<jt::Sound>(fileName, ctx));
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
