#include "sound_buffer_manager.hpp"
#include <oalpp/sound_data/sound_data.hpp>
#include <oalpp/sound_data/sound_data_builder.hpp>

std::shared_ptr<oalpp::SoundDataInterface> jt::SoundBufferManager::get(std::string const& fileName)
{
    if (!m_soundBuffers.contains(fileName)) {
        oalpp::SoundDataBuilder builder;
        m_soundBuffers[fileName]
            = std::make_shared<oalpp::SoundData>(builder.fromFile(fileName).create());
    }

    return m_soundBuffers[fileName];
}

std::shared_ptr<oalpp::SoundDataInterface> jt::SoundBufferManager::get(std::string const& fileName,
    std::string const& identifier, oalpp::effects::MonoEffectInterface& effect)
{
    auto const fullName = fileName + "#" + identifier;
    if (!m_soundBuffers.contains(fullName)) {
        auto const originalData = get(fileName);
        oalpp::SoundDataBuilder builder;
        m_soundBuffers[fullName] = std::make_shared<oalpp::SoundData>(
            builder.fromExistingSoundData(*originalData.get()).withEffect(effect).create());
    }
    return m_soundBuffers[fullName];
}

std::size_t jt::SoundBufferManager::getNumberOfBuffers() const { return m_soundBuffers.size(); }

bool jt::SoundBufferManager::contains(std::string const& filename)
{
    return m_soundBuffers.contains(filename);
}
