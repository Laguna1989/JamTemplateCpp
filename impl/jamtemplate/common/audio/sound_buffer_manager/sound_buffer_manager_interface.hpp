#ifndef JAMTEMPLATE_SOUND_BUFFER_MANAGER_INTERFACE_HPP
#define JAMTEMPLATE_SOUND_BUFFER_MANAGER_INTERFACE_HPP

#include <oalpp/effects/mono_effect_interface.hpp>
#include <oalpp/sound_data/sound_data_interface.hpp>
#include <cstddef>
#include <memory>
#include <string>

namespace jt {

class SoundBufferManagerInterface {
public:
    virtual std::shared_ptr<oalpp::SoundDataInterface> get(std::string const& fileName) = 0;
    virtual std::shared_ptr<oalpp::SoundDataInterface> get(std::string const& fileName,
        std::string const& identifier, oalpp::effects::MonoEffectInterface& effect)
        = 0;

    virtual std::size_t getNumberOfBuffers() const = 0;

    virtual bool contains(std::string const& filename) = 0;

    virtual ~SoundBufferManagerInterface() = default;

    // no copy, no move. Avoid slicing.
    SoundBufferManagerInterface(SoundBufferManagerInterface const&) = delete;
    SoundBufferManagerInterface(SoundBufferManagerInterface&&) = delete;
    SoundBufferManagerInterface& operator=(SoundBufferManagerInterface const&) = delete;
    SoundBufferManagerInterface& operator=(SoundBufferManagerInterface&&) = delete;

protected:
    // default constructor can only be called from derived classes
    SoundBufferManagerInterface() = default;
};

} // namespace jt

#endif // JAMTEMPLATE_SOUND_BUFFER_MANAGER_INTERFACE_HPP
