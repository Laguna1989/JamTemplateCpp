#include "sound_null.hpp"

namespace jt {
void SoundNull::update() { }
bool SoundNull::isPlaying() const { return false; }
void SoundNull::play() { }
void SoundNull::stop() { }
float SoundNull::getVolume() const { return 0; }
void SoundNull::setVolume(float newVolume) { }
void SoundNull::setLoop(bool doLoop) { }
bool SoundNull::getLoop(void) { return false; }
float SoundNull::getDuration() const { return 0; }
float SoundNull::getPosition() const { return 0; }
} // namespace jt
