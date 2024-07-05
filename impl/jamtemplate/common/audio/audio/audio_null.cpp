#include "audio_null.hpp"
#include <audio/sound/sound_null.hpp>

void jt::null_objects::AudioNull::update(float /*elapsed*/) { }

std::shared_ptr<jt::SoundInterface> jt::null_objects::AudioNull::getPermanentSound(
    std::string const& /*identifier*/)
{
    return std::make_shared<SoundNull>();
}

std::shared_ptr<jt::SoundInterface> jt::null_objects::AudioNull::addTemporarySound(
    std::string const& /*fileName*/)
{
    return std::make_shared<jt::SoundNull>();
}

std::shared_ptr<jt::SoundInterface> jt::null_objects::AudioNull::addPermanentSound(
    std::string const& /*identifier*/, std::string const& /*fileName*/)
{
    return std::make_shared<jt::SoundNull>();
}
