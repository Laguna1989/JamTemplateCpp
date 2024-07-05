#include "audio_impl.hpp"
#include "performance_measurement.hpp"
#include <audio/sound/sound.hpp>
#include <random/random.hpp>

jt::AudioImpl::AudioImpl() = default;

jt::AudioImpl::~AudioImpl() { }

void jt::AudioImpl::update(float elapsed)
{
    // TODO(Simon)
}

std::shared_ptr<jt::SoundInterface> jt::AudioImpl::addTemporarySound(std::string const& fileName)
{
    // TODO(Simon)
    return nullptr;
}

std::shared_ptr<jt::SoundInterface> jt::AudioImpl::addPermanentSound(
    std::string const& identifier, std::string const& fileName)
{
    // TODO(Simon)
    return std::shared_ptr<jt::SoundInterface>();
}

std::shared_ptr<jt::SoundInterface> jt::AudioImpl::getPermanentSound(std::string const& identifier)
{
    // TODO(Simon)
    return std::shared_ptr<jt::SoundInterface>();
}
