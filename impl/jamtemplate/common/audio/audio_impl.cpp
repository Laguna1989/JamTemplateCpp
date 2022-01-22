#include "audio_impl.hpp"
#include "sound.hpp"
#include <algorithm>

namespace jt {

AudioImpl::~AudioImpl()
{
    m_sounds.clear();
    m_music.reset();
}

std::shared_ptr<SoundInterface> AudioImpl::createSound(std::string const& fileName)
{
    auto snd = std::make_shared<Sound>(fileName, m_context);
    m_sounds.push_back(snd);
    return snd;
}

void AudioImpl::playMusic(std::string const& fileName)
{
    m_music = createSound(fileName);
    m_music->setLoop(true);
    m_music->play();
}

void AudioImpl::update()
{
    cleanUpUnusedSounds();

    for (auto const& snd : m_sounds) {
        auto sound = snd.lock();
        if (sound) {
            sound->update();
        }
    }
}
void AudioImpl::cleanUpUnusedSounds()
{
    m_sounds.erase(
        std::remove_if(m_sounds.begin(), m_sounds.end(), [](auto wptr) { return wptr.expired(); }),
        m_sounds.end());
}

} // namespace jt
