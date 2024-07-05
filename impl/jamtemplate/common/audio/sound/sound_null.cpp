#include "sound_null.hpp"

bool jt::SoundNull::isPlaying() const { return false; }

void jt::SoundNull::play() { }

void jt::SoundNull::pause() { }

void jt::SoundNull::stop() { }

float jt::SoundNull::getVolume() const { return 0.0f; }

void jt::SoundNull::setVolume(float /*newVolume*/) { }
