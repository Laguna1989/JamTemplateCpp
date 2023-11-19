#include "audio_null.hpp"
#include <audio/sound/sound_group.hpp>
#include <audio/sound/sound_null.hpp>

void jt::null_objects::AudioNull::update(float /*elapsed*/) { }

oalpp::SoundContextInterface& jt::null_objects::AudioNull::getContext() { return m_context; }

std::shared_ptr<jt::SoundInterface> jt::null_objects::AudioNull::soundPool(
    std::string const& /*baseIdentifier*/, std::string const& /*fileName*/, std::size_t /*count*/)
{
    return std::make_shared<SoundNull>();
}

std::shared_ptr<jt::SoundInterface> jt::null_objects::AudioNull::getPermanentSound(
    std::string const& /*identifier*/)
{
    return std::make_shared<SoundNull>();
}

void jt::null_objects::AudioNull::removePermanentSound(std::string const& /*identifier*/) { }

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

std::shared_ptr<jt::SoundInterface> jt::null_objects::AudioNull::addPermanentSound(
    std::string const& /*identifier*/, std::string const& /*fileName*/,
    oalpp::effects::MonoEffectInterface& /*effect*/)
{
    return std::make_shared<jt::SoundNull>();
}

std::shared_ptr<jt::SoundInterface> jt::null_objects::AudioNull::addPermanentSound(
    std::string const& /*identifier*/, std::string const& /*introFileName*/,
    std::string const& /*loopingFileName*/, oalpp::effects::MonoEffectInterface& /*effect*/)
{
    return std::make_shared<jt::SoundNull>();
}

std::shared_ptr<jt::SoundInterface> jt::null_objects::AudioNull::addTemporarySoundGroup(
    std::vector<std::shared_ptr<jt::SoundInterface>> const& sounds)
{
    auto group = std::make_shared<jt::SoundGroup>();

    for (auto const& _ : sounds) {
        (void)_;
        group->add(std::make_shared<jt::SoundNull>());
    }

    return group;
}

jt::SoundFadeManagerInterface& jt::null_objects::AudioNull::fades() { return *m_fades; }

jt::GroupVolumeSetterInterface& jt::null_objects::AudioNull::groups() { return m_groups; }

jt::SoundBufferManagerInterface& jt::null_objects::AudioNull::getSoundBufferManager()
{
    return m_nullManager;
}
