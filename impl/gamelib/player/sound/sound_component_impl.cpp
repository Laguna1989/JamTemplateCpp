#include "sound_component_impl.hpp"
#include <audio/sound/logging_sound.hpp>
#include <audio/sound/sound.hpp>
#include <audio/sound/sound_group.hpp>
#include <audio/sound/sound_null.hpp>

SoundComponentImpl::SoundComponentImpl(
    jt::AudioInterface& /*audio*/, jt::LoggerInterface& /*logger*/)
{
    // TODO load Sounds
}

void SoundComponentImpl::play(SoundComponentInterface::SoundId /*sound*/)
{
    // TODO Play sounds based on ID
}

bool SoundComponentImpl::isPlaying(SoundComponentInterface::SoundId /*sound*/)
{
    // TODO return value based on ID
    return false;
}
