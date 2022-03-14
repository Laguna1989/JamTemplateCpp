#include "audio_impl.hpp"
#include "random/random.hpp"
#include "sound.hpp"
#include <algorithm>

namespace jt {

AudioImpl::~AudioImpl() { m_temporarySounds.clear(); }

void AudioImpl::update()
{
    cleanUpUnusedSounds();

    for (auto const& snd : m_temporarySounds) {
        auto sound = snd.lock();
        if (sound) {
            sound->update();
        }
    }
    for (auto& snd : m_permanentSounds) {
        snd.second->update();
    }
}
void AudioImpl::cleanUpUnusedSounds()
{
    m_temporarySounds.erase(std::remove_if(m_temporarySounds.begin(), m_temporarySounds.end(),
                                [](auto wptr) { return wptr.expired(); }),
        m_temporarySounds.end());
}

void AudioImpl::addTemporarySound(std::weak_ptr<SoundInterface> snd)
{
    m_temporarySounds.push_back(snd);
}

oalpp::SoundContextInterface& AudioImpl::getContext() { return m_context; }

void AudioImpl::addPermanentSound(
    std::string const& identifier, std::shared_ptr<SoundInterface> snd)
{
    m_permanentSounds[identifier] = snd;
}

std::shared_ptr<SoundInterface> AudioImpl::getPermanentSound(std::string const& identifier)
{
    if (m_permanentSounds.count(identifier) == 0) {
        return nullptr;
    }
    return m_permanentSounds[identifier];
}

void AudioImpl::removePermanentSound(std::string const& identifier)
{
    if (m_permanentSounds.count(identifier) != 0) {
        m_permanentSounds[identifier] = nullptr;
    }
}

std::shared_ptr<SoundInterface> AudioImpl::soundPool(std::string const& baseIdentifier,
    std::function<std::shared_ptr<SoundInterface>()> function, std::size_t count)
{
    auto const randomNumber = jt::Random::getInt(0, count);
    auto const soundName = "identifier####" + std::to_string(randomNumber);

    auto snd = getPermanentSound(soundName);
    if (snd == nullptr) {
        snd = function();
        addPermanentSound(soundName, snd);
    }
    return snd;
}

} // namespace jt
