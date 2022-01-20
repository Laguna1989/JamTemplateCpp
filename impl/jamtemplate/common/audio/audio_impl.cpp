#include "audio_impl.hpp"
#include "sound.hpp"

namespace jt {
std::shared_ptr<SoundInterface> AudioImpl::createSound(std::string const& fileName)
{
    auto snd = std::make_shared<Sound>(fileName, m_context);
    m_sounds.push_back(snd);
    return snd;
}

void AudioImpl::removeSound(std::shared_ptr<SoundInterface> snd)
{
    // TODO
}

void AudioImpl::update()
{
    for (auto const& snd : m_sounds) {
        snd->update();
    }
}
} // namespace jt
