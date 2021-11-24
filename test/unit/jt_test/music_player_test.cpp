#include "music_player.hpp"
#include <gtest/gtest.h>

TEST(MusicPlayerTest, InitialVolume)
{
    jt::MusicPlayer player {};
    ASSERT_EQ(player.getMusicVolume(), 0.0f);
}

TEST(MusicPlayerTest, InitialFileName)
{
    jt::MusicPlayer player {};
    ASSERT_EQ(player.getMusicFilePath(), "");
}

TEST(MusicPlayerTest, VolumeAfterPlay)
{
    jt::MusicPlayer player {};
    player.playMusic("assets/test.wav");
    ASSERT_EQ(player.getMusicVolume(), 100.0f);
}

TEST(MusicPlayerTest, FileNameAfterPlay)
{
    jt::MusicPlayer player {};
    player.playMusic("assets/test.wav");
    ASSERT_EQ(player.getMusicFilePath(), "assets/test.wav");
}

TEST(MusicPlayerTest, VolumeResetAfterPlay)
{
    jt::MusicPlayer player {};
    player.playMusic("assets/test.wav");
    player.setMusicVolume(0.0f);
    player.playMusic("assets/test.wav");
    ASSERT_EQ(player.getMusicVolume(), 100.0f);
}

TEST(MusicPlayerTest, StopWithoutPlay)
{
    jt::MusicPlayer player {};

    player.stopMusic();
}

TEST(MusicPlayerTest, StopAfterPlay)
{
    jt::MusicPlayer player {};
    player.playMusic("assets/test.wav");
    player.stopMusic();
}
