#include "music_player.hpp"
#include <gtest/gtest.h>

TEST(MusicPlayerTest, InitialVolume)
{
    jt::MusicPlayer player {};
    ASSERT_EQ(player.GetMusicVolume(), 0.0f);
}

TEST(MusicPlayerTest, InitialFileName)
{
    jt::MusicPlayer player {};
    ASSERT_EQ(player.GetMusicFilePath(), "");
}

TEST(MusicPlayerTest, VolumeAfterPlay)
{
    jt::MusicPlayer player {};
    player.PlayMusic("assets/test.wav");
    ASSERT_EQ(player.GetMusicVolume(), 100.0f);
}

TEST(MusicPlayerTest, FileNameAfterPlay)
{
    jt::MusicPlayer player {};
    player.PlayMusic("assets/test.wav");
    ASSERT_EQ(player.GetMusicFilePath(), "assets/test.wav");
}

TEST(MusicPlayerTest, VolumeResetAfterPlay)
{
    jt::MusicPlayer player {};
    player.PlayMusic("assets/test.wav");
    player.SetMusicVolume(0.0f);
    player.PlayMusic("assets/test.wav");
    ASSERT_EQ(player.GetMusicVolume(), 100.0f);
}

TEST(MusicPlayerTest, StopWithoutPlay)
{
    jt::MusicPlayer player {};

    player.StopMusic();
}

TEST(MusicPlayerTest, StopAfterPlay)
{
    jt::MusicPlayer player {};
    player.PlayMusic("assets/test.wav");
    player.StopMusic();
}
