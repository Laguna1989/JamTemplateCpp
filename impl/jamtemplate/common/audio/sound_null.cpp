#include "sound_null.hpp"

void jt::SoundNull::update() { }
bool jt::SoundNull::isPlaying() const { return false; }
void jt::SoundNull::play() { }
void jt::SoundNull::stop() { }
float jt::SoundNull::getVolume() const { return 0; }
void jt::SoundNull::setVolume(float /*newVolume*/) { }
void jt::SoundNull::setLoop(bool /*doLoop*/) { }
bool jt::SoundNull::getLoop(void) { return false; }
float jt::SoundNull::getDuration() const { return 0; }
float jt::SoundNull::getPosition() const { return 0; }
void jt::SoundNull::setBlend(float /*blend*/) { }
float jt::SoundNull::getBlend() const { return 0; }
void jt::SoundNull::pause() { }
int jt::SoundNull::getSampleRate() const { return 0; }
