#include <audio/sound_null.hpp>
#include <gtest/gtest.h>

TEST(SoundNullTest, UpdateDoesNotThrowException)
{
    jt::SoundNull snd;
    ASSERT_NO_THROW(snd.update());
}

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

TEST(SoundNullTest, SetLoopDoesNotThrowException)
{
    jt::SoundNull snd;
    ASSERT_NO_THROW(snd.setLoop(true));
    ASSERT_NO_THROW(snd.setLoop(false));
}

TEST(SoundNullTest, GetLoopReturnsFalse)
{
    jt::SoundNull snd;
    ASSERT_FALSE(snd.getLoop());
}

TEST(SoundNullTest, GetDurationReturns0)
{
    jt::SoundNull snd;
    ASSERT_EQ(snd.getDuration(), 0.0f);
}

TEST(SoundNullTest, GetPositionReturns0)
{
    jt::SoundNull snd;
    ASSERT_EQ(snd.getPosition(), 0.0f);
}

TEST(SoundNullTest, GetBlendReturns0)
{
    jt::SoundNull snd;
    ASSERT_EQ(snd.getBlend(), 0.0f);
}

TEST(SoundNullTest, SetBlendDoesNotThrow)
{
    jt::SoundNull snd;
    ASSERT_NO_THROW(snd.setBlend(0.0f));
}

TEST(SoundNullTest, GetSampleRateReturns44100)
{
    jt::SoundNull snd;
    ASSERT_EQ(snd.getSampleRate(), 44100);
}

TEST(SoundNullTest, GetPitchReturns0)
{
    jt::SoundNull snd;
    ASSERT_EQ(snd.getPitch(), 1.0f);
}

TEST(SoundNullTest, SetPitchDoesNotThrow)
{
    jt::SoundNull snd;
    ASSERT_NO_THROW(snd.setPitch(0.0f));
    ASSERT_NO_THROW(snd.setPitch(1.0f));
    ASSERT_NO_THROW(snd.setPitch(2.0f));
}
