#include "sound_data_null.hpp"

int jt::null_objects::SoundDataNull::getNumberOfChannels() const { return 1; }

int jt::null_objects::SoundDataNull::getSampleRate() const { return 44100; }

std::vector<float> const& jt::null_objects::SoundDataNull::getSamples() const { return m_samples; }
