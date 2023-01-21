#include "audio_null.hpp"
#include <audio/sound_group.hpp>
#include <audio/sound_null.hpp>

void jt::AudioNull::update(float /*elapsed*/) { }
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

std::shared_ptr<jt::SoundInterface> jt::AudioNull::addTemporarySoundGroup(
    std::vector<std::shared_ptr<jt::SoundInterface>> const& sounds)
{
    auto group = std::make_shared<jt::SoundGroup>();

    for (auto const& sound : sounds) {
        group->add(std::make_shared<jt::SoundNull>());
    }

    return group;
}
jt::SoundFadeManager& jt::AudioNull::fades() { return m_fades; }
jt::GroupVolumeSetterInterface& jt::AudioNull::groups() { return m_groups; }
