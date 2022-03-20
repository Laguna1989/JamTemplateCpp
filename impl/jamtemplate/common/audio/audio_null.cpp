#include "audio_null.hpp"
#include "sound_null.hpp"

void jt::AudioNull::update() { }
oalpp::SoundContextInterface& jt::AudioNull::getContext() { return m_context; }
void jt::AudioNull::addTemporarySound(std::weak_ptr<jt::SoundInterface> snd) { }
void jt::AudioNull::addPermanentSound(
    std::string const& identifier, std::shared_ptr<jt::SoundInterface> snd)
{
}

std::shared_ptr<jt::SoundInterface> jt::AudioNull::soundPool(std::string const& baseIdentifier,
    std::function<std::shared_ptr<jt::SoundInterface>()> function, std::size_t count)
{
    return std::make_shared<SoundNull>();
}

std::shared_ptr<jt::SoundInterface> jt::AudioNull::getPermanentSound(std::string const& identifier)
{
    return std::make_shared<SoundNull>();
}

void jt::AudioNull::removePermanentSound(std::string const& identifier) { }
