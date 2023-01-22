#include "sound_null.hpp"

void jt::SoundNull::update() { }
bool jt::SoundNull::isPlaying() const { return false; }

void jt::SoundNull::play() { }
void jt::SoundNull::pause() { }
void jt::SoundNull::stop() { }

float jt::SoundNull::getVolume() const { return 0; }
void jt::SoundNull::setVolume(float /*newVolume*/) { }

void jt::SoundNull::setLoop(bool /*doLoop*/) { }
bool jt::SoundNull::getLoop(void) { return false; }

float jt::SoundNull::getDuration() const { return 0; }
float jt::SoundNull::getPosition() const { return 0; }

void jt::SoundNull::setBlend(float /*blend*/) { }
float jt::SoundNull::getBlend() const { return 0; }

int jt::SoundNull::getSampleRate() const { return 44100; }

void jt::SoundNull::setPitch(float /*pitch*/) { }
float jt::SoundNull::getPitch() const { return 1.0f; }

void jt::SoundNull::setVolumeProvider(jt::GroupVolumeGetterInterface& provider) { }
void jt::SoundNull::setVolumeGroup(std::string const& string) { }
