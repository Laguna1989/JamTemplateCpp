#include "music_player_null.hpp"

void jt::MusicPlayerNull::PlayMusic(std::string const& fileName) { m_filename = fileName; }
void jt::MusicPlayerNull::StopMusic() { }
void jt::MusicPlayerNull::SetMusicVolume(float v) { m_volume = v; }
float jt::MusicPlayerNull::GetMusicVolume() { return m_volume; }
std::string jt::MusicPlayerNull::GetMusicFilePath() { return m_filename; }
