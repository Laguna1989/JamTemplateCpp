#ifndef JAMTEMPLATE_SOUND_BUFFER_MANAGER_NULL_HPP
#define JAMTEMPLATE_SOUND_BUFFER_MANAGER_NULL_HPP

#include <audio/sound_buffer_manager/sound_buffer_manager_interface.hpp>

namespace jt {

namespace null_objects {

class SoundBufferManagerNull : public jt::SoundBufferManagerInterface {
public:
    std::shared_ptr<oalpp::SoundDataInterface> get(std::string const& fileName) override;
    std::shared_ptr<oalpp::SoundDataInterface> get(std::string const& fileName,
        std::string const& identifier, oalpp::effects::MonoEffectInterface& effect) override;
    size_t getNumberOfBuffers() const override;
    bool contains(std::string const& filename) override;
};

} // namespace null_objects

} // namespace jt

#endif // JAMTEMPLATE_SOUND_BUFFER_MANAGER_NULL_HPP
