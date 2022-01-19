#include "music_player_null.hpp"

void jt::MusicPlayerNull::playMusic(std::string const& fileName) { m_filename = fileName; }
void jt::MusicPlayerNull::stopMusic() { }
void jt::MusicPlayerNull::setMusicVolume(float v) { m_volume = v; }
float jt::MusicPlayerNull::getMusicVolume() { return m_volume; }
std::string jt::MusicPlayerNull::getMusicFilePath() { return m_filename; }
void jt::MusicPlayerNull::update() { }
