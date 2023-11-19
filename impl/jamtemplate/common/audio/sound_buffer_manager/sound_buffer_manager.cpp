#include "sound_buffer_manager.hpp"
#include <oalpp/sound_data/sound_data.hpp>
#include <oalpp/sound_data/sound_data_with_effect.hpp>

std::shared_ptr<oalpp::SoundDataInterface> jt::SoundBufferManager::get(std::string const& fileName)
{
    if (!m_soundBuffers.contains(fileName)) {
        m_soundBuffers[fileName] = std::make_shared<oalpp::SoundData>(fileName);
    }

    return m_soundBuffers[fileName];
}

std::shared_ptr<oalpp::SoundDataInterface> jt::SoundBufferManager::get(std::string const& fileName,
    std::string const& identifier, oalpp::effects::MonoEffectInterface& effect)
{
    auto const fullName = fileName + "#" + identifier;
    if (!m_soundBuffers.contains(fullName)) {
        std::shared_ptr<oalpp::SoundDataInterface> rawSoundData { get(fileName) };
        m_soundBuffers[fullName]
            = std::make_shared<oalpp::SoundDataWithEffect>(*rawSoundData, effect);
    }
    return m_soundBuffers[fullName];
}

std::size_t jt::SoundBufferManager::getNumberOfBuffers() const { return m_soundBuffers.size(); }

bool jt::SoundBufferManager::contains(std::string const& filename)
{
    return m_soundBuffers.contains(filename);
}
