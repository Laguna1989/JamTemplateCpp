#ifndef JAMTEMPLATE_SOUND_DATA_NULL_HPP
#define JAMTEMPLATE_SOUND_DATA_NULL_HPP

#include <oalpp/sound_data/sound_data_interface.hpp>

namespace jt {

namespace null_objects {

class SoundDataNull : public oalpp::SoundDataInterface {
public:
    int getNumberOfChannels() const override;
    int getSampleRate() const override;
    std::vector<float> const& getSamples() const override;

private:
    std::vector<float> m_samples;
};

} // namespace null_objects

} // namespace jt

#endif // JAMTEMPLATE_SOUND_DATA_NULL_HPP
