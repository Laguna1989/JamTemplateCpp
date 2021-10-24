#include "sound_group.hpp"
#include "random.hpp"
#include "sound.hpp"
#include <algorithm>

namespace {
std::shared_ptr<jt::Sound> loadSound(std::string const& filename)
{
    auto snd = std::make_shared<jt::Sound>();
    snd->load(filename);
    return snd;
}
} // namespace

jt::SoundGroup::SoundGroup(std::vector<std::string> const& sounds)
{
    for (auto const& f : sounds) {
        m_sounds.emplace_back(loadSound(f));
    }
    m_isInitialized = true;
}

void jt::SoundGroup::doLoad(std::string const& fileName)
{
    m_sounds.emplace_back(loadSound(fileName));
}

bool jt::SoundGroup::doIsPlaying() const
{
    return std::any_of(m_sounds.cbegin(), m_sounds.cend(),
        [](std::shared_ptr<SoundBase> const& snd) { return snd->isPlaying(); });
}

void jt::SoundGroup::doPlay()
{
    if (m_sounds.empty()) {
        return;
    }

    std::size_t const index = Random::getInt(0, static_cast<int>(m_sounds.size()) - 1);
    m_sounds.at(index)->play();
}

void jt::SoundGroup::doStop()
{
    for (auto& snd : m_sounds) {
        snd->stop();
    }
}

float jt::SoundGroup::doGetVolume() const
{
    if (m_sounds.empty()) {
        return 0.0f;
    }
    return m_sounds.at(0)->getVolume();
}

void jt::SoundGroup::doSetVolume(float newVolume)
{
    for (auto& snd : m_sounds) {
        snd->setVolume(newVolume);
    }
}

void jt::SoundGroup::doSetLoop(bool doLoop)
{
    for (auto& snd : m_sounds) {
        snd->setLoop(doLoop);
    }
}

bool jt::SoundGroup::doGetLoop()
{
    if (m_sounds.empty()) {
        return false;
    }
    return m_sounds.at(0)->getLoop();
}

float jt::SoundGroup::doGetDuration() const { return 0.0f; }

float jt::SoundGroup::doGetPosition() const { return 0.0f; }
