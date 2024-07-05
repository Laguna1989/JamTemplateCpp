#include <audio/sound/sound_null.hpp>
#include <gtest/gtest.h>

TEST(SoundNullTest, isPlayingReturnsFalse)
{
    jt::SoundNull snd;
    ASSERT_FALSE(snd.isPlaying());
}

TEST(SoundNullTest, PlayDoesNotThrowException)
{
    jt::SoundNull snd;
    ASSERT_NO_THROW(snd.play());
}

TEST(SoundNullTest, PauseDoesNotThrowException)
{
    jt::SoundNull snd;
    ASSERT_NO_THROW(snd.pause());
}

TEST(SoundNullTest, StopDoesNotThrowException)
{
    jt::SoundNull snd;
    ASSERT_NO_THROW(snd.stop());
}

TEST(SoundNullTest, SetVolumeDoesNotThrowException)
{
    jt::SoundNull snd;
    ASSERT_NO_THROW(snd.setVolume(0.5f));
}

TEST(SoundNullTest, GetVolumeReturnsZero)
{
    jt::SoundNull snd;
    ASSERT_EQ(snd.getVolume(), 0.0f);
}
