#include "sound_buffer_manager_null.hpp"
#include <audio/sound/sound_data_null.hpp>

std::shared_ptr<oalpp::SoundDataInterface> jt::null_objects::SoundBufferManagerNull::get(
    std::string const& /*fileName*/)
{
    return std::make_shared<jt::null_objects::SoundDataNull>();
}

std::shared_ptr<oalpp::SoundDataInterface> jt::null_objects::SoundBufferManagerNull::get(
    std::string const& /*fileName*/, std::string const& /*identifier*/,
    oalpp::effects::MonoEffectInterface& /*effect*/)
{
    return std::make_shared<jt::null_objects::SoundDataNull>();
}

bool jt::null_objects::SoundBufferManagerNull::contains(std::string const& /*filename*/)
{
    return false;
}

size_t jt::null_objects::SoundBufferManagerNull::getNumberOfBuffers() const { return 0; }
