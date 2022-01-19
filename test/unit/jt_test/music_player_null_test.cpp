#include "audio/music_player_null.hpp"
#include <gtest/gtest.h>

TEST(MusicPlayerNullTest, FilePathAfterPlay)
{
    jt::MusicPlayerNull player;
    player.playMusic("abcd");
    ASSERT_EQ(player.getMusicFilePath(), "abcd");
}

TEST(MusicPlayerNullTest, MusicVolumeAfterSetVolume)
{
    jt::MusicPlayerNull player;
    player.setMusicVolume(50.0f);
    ASSERT_EQ(player.getMusicVolume(), 50.0f);
}

TEST(MusicPlayerNullTest, StopMusicDoesNotThrow)
{
    jt::MusicPlayerNull player;
    ASSERT_NO_THROW(player.stopMusic());
}
