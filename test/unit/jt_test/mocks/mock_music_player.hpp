#ifndef GUARD_JAMTEMPLATE_MOCK_MUSIC_PLAYER_HPP
#define GUARD_JAMTEMPLATE_MOCK_MUSIC_PLAYER_HPP

#include "audio/music_player_interface.hpp"
#include <gmock/gmock.h>

class MockMusicPlayer : public jt::MusicPlayerInterface {
public:
    MOCK_METHOD(void, playMusic, (std::string const& fileName), (override));
    MOCK_METHOD(void, stopMusic, (), (override));
    MOCK_METHOD(void, setMusicVolume, (float v), (override));
    MOCK_METHOD(float, getMusicVolume, (), (override));
    MOCK_METHOD(std::string, getMusicFilePath, (), (override));
};

#endif // GUARD_JAMTEMPLATE_MOCK_MUSIC_PLAYER_HPP
