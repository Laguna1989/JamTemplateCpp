#ifndef JAMTEMPLATE_SOUND_BUFFER_MANAGER_HPP
#define JAMTEMPLATE_SOUND_BUFFER_MANAGER_HPP

#include "sound_buffer_manager_interface.hpp"
#include <map>
#include <memory>
#include <string>

namespace jt {

class SoundBufferManager : public jt::SoundBufferManagerInterface {
public:
    std::shared_ptr<oalpp::SoundDataInterface> get(std::string const& fileName) override;
    std::shared_ptr<oalpp::SoundDataInterface> get(std::string const& fileName,
        std::string const& identifier, oalpp::effects::MonoEffectInterface& effect) override;
    std::size_t getNumberOfBuffers() const override;

    bool contains(std::string const& filename) override;

private:
    std::map<std::string, std::shared_ptr<oalpp::SoundDataInterface>> m_soundBuffers;
};

} // namespace jt

#endif // JAMTEMPLATE_SOUND_BUFFER_MANAGER_HPP
