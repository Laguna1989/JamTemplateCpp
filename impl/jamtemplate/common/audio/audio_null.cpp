#include "audio_null.hpp"
#include <audio/sound_null.hpp>

void jt::AudioNull::update() { }
oalpp::SoundContextInterface& jt::AudioNull::getContext() { return m_context; }

std::shared_ptr<jt::SoundInterface> jt::AudioNull::soundPool(
    std::string const& /*baseIdentifier*/, std::string const& /*fileName*/, std::size_t /*count*/)
{
    return std::make_shared<SoundNull>();
}

std::shared_ptr<jt::SoundInterface> jt::AudioNull::getPermanentSound(
    std::string const& /*identifier*/)
{
    return std::make_shared<SoundNull>();
}

void jt::AudioNull::removePermanentSound(std::string const& /*identifier*/) { }

std::shared_ptr<jt::SoundInterface> jt::AudioNull::addTemporarySound(
    std::string const& /*fileName*/)
{
    return std::make_shared<jt::SoundNull>();
}

std::shared_ptr<jt::SoundInterface> jt::AudioNull::addPermanentSound(
    std::string const& /*identifier*/, std::string const& /*fileName*/)
{
    return std::make_shared<jt::SoundNull>();
}
std::shared_ptr<jt::SoundInterface> jt::AudioNull::addPermanentSound(
    std::string const& /*identifier*/, std::string const& /*fileName*/,
    oalpp::effects::MonoEffectInterface& /*effect*/)
{
    return std::make_shared<jt::SoundNull>();
}
std::shared_ptr<jt::SoundInterface> jt::AudioNull::addPermanentSound(std::string const& identifier,
    std::string const& introFileName, std::string const& loopingFileName,
    oalpp::effects::MonoEffectInterface& effect)
{
    return std::make_shared<jt::SoundNull>();
}
