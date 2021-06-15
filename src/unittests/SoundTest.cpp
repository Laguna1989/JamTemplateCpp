#include "Sound.hpp"
#include "gtest/gtest.h"
#include <limits>
#include <thread>
#include <type_traits>

using jt::Sound;

void init()
{
    // in a normal game executable the sdl audio init would happen in the game class.
    // as this test should not need to know about the game, it needs to be done here.
#ifdef ENABLE_WEB
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_Init(MIX_INIT_OGG);
#endif
}

TEST(SoundTest, SoundImplIsDerivedFromSoundBase)
{
    static_assert(
        std::is_base_of<jt::SoundBase, jt::Sound>::value, "Sound is not derived from SoundBase");
}

TEST(SoundTest, SoundWithoutLoadIsNotInitialized)
{
    init();
    Sound s {};
    EXPECT_FALSE(s.isInitialized());
}

TEST(SoundTest, LoadWav)
{
    init();
    Sound s {};
    EXPECT_NO_THROW(s.load("assets/test.wav"));
}

TEST(SoundTest, LoadOgg)
{
    init();
    Sound s {};
    EXPECT_NO_THROW(s.load("assets/test.ogg"));
}

TEST(SoundTest, SoundWithLoadIsInitialized)
{
    init();
    Sound s {};
    s.load("assets/test.wav");
    EXPECT_TRUE(s.isInitialized());
}

TEST(SoundTest, SoundIsNotPlayingByDefault)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    EXPECT_FALSE(s.isPlaying());
}

TEST(SoundTest, SoundIsPlayingReturnsTrueAfterPlay)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    s.play();
    EXPECT_TRUE(s.isPlaying());
}

TEST(SoundTest, DefaultVolume)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    EXPECT_EQ(s.getVolume(), 100.0f);
}

TEST(SoundTest, GetVolumeAfterSetVolume)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    float const newVolume = 25.245f;
    s.setVolume(newVolume);
    EXPECT_FLOAT_EQ(s.getVolume(), newVolume);
}

TEST(SoundTest, SetVolumeZero)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    float const newVolume = 0.0f;
    s.setVolume(newVolume);
    EXPECT_FLOAT_EQ(s.getVolume(), newVolume);
}

TEST(SoundTest, SetVolumeHundret)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    float const newVolume = 100.0f;
    s.setVolume(newVolume);
    EXPECT_FLOAT_EQ(s.getVolume(), newVolume);
}

TEST(SoundTest, StopDoesNothingWhenNotPlaying)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    ASSERT_FALSE(s.isPlaying());
    s.stop();
    EXPECT_FALSE(s.isPlaying());
}

TEST(SoundTest, StopPlayingSound)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    s.play();
    ASSERT_TRUE(s.isPlaying());
    s.stop();
    EXPECT_FALSE(s.isPlaying());
}

TEST(SoundTest, GetLoopReturnsFalseOnDefault)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    EXPECT_FALSE(s.getLoop());
}

TEST(SoundTest, GetLoopAfterSetLoop)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    s.setLoop(true);
    EXPECT_TRUE(s.getLoop());
}

TEST(SoundTest, GetPositionAfterLoad)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    EXPECT_FLOAT_EQ(s.getPosition(), 0.0f);
}

TEST(SoundCornerCaseTests, LoadTwice)
{
    init();
    Sound s {};
    EXPECT_NO_THROW(s.load("assets/test.ogg"));
    EXPECT_NO_THROW(s.load("assets/test.wav"));
}

TEST(SoundCornerCaseTests, DeleteWithoutLoad)
{
    init();
    {
        Sound s {};
    }
}

TEST(SoundCornerCaseTests, PlayTwice)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    EXPECT_NO_THROW(s.play());
    EXPECT_NO_THROW(s.play());
}

TEST(SoundCornerCaseTests, StopTwice)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    EXPECT_NO_THROW(s.play());
    EXPECT_NO_THROW(s.stop());
    EXPECT_NO_THROW(s.stop());
}

TEST(SoundCornerCaseTests, PlayAfterStop)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    EXPECT_NO_THROW(s.play());
    EXPECT_NO_THROW(s.stop());
    EXPECT_NO_THROW(s.play());
}

TEST(SoundCornerCaseTests, SetVolumeWhilePlaying)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    EXPECT_NO_THROW(s.play());
    ASSERT_TRUE(s.isPlaying());
    EXPECT_NO_THROW(s.setVolume(55.5f));
    EXPECT_NO_THROW(s.setVolume(2.5f));
    EXPECT_NO_THROW(s.setVolume(100.0f));
}

#ifndef ENABLE_WEB

TEST(SoundTest, GetPositionAfterPlay)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    s.play();
    // note: play will happen in another thread, so in order to progress the
    // position, this test needs to sleep a bit.
    std::this_thread::sleep_for(std::chrono::milliseconds { 100U });
    EXPECT_NE(s.getPosition(), 0.0f);
}
TEST(SoundTest, GetDurationReturnsExpectedValue)
{
    init();
    Sound s {};
    s.load("assets/test.ogg");
    auto const d = s.getDuration();
    float const expected { 0.262721002f };
    EXPECT_FLOAT_EQ(d, expected);
}

TEST(SoundTest, InvalidLoadThrowsException)
{
    Sound s {};
    EXPECT_ANY_THROW(s.load("non-existing-file.wav"));
}

TEST(SoundTest, IsPlayingThrowsForUninitializedSound)
{
    Sound s {};
    ASSERT_FALSE(s.isInitialized());
    EXPECT_ANY_THROW(s.isPlaying());
}

TEST(SoundTest, PlayThrowsForUninitializedSound)
{
    Sound s {};
    EXPECT_ANY_THROW(s.play());
}

TEST(SoundTest, GetVolumeThrowsForUninitializedSound)
{
    Sound s {};
    EXPECT_ANY_THROW(s.getVolume());
}

TEST(SoundTest, SetVolumeThrowsForUninitializedSound)
{
    Sound s {};
    ASSERT_FALSE(s.isInitialized());
    float const newVolume = 25.245f;
    EXPECT_ANY_THROW(s.setVolume(newVolume));
}

TEST(SoundTest, StopThrowsForUninitializedSound)
{
    Sound s {};
    EXPECT_ANY_THROW(s.stop());
}
TEST(SoundTest, SetLoopThrowsForUninitializedSound)
{
    Sound s {};
    EXPECT_ANY_THROW(s.setLoop(true));
}

TEST(SoundTest, GetLoopThrowsForUninitializedSound)
{
    Sound s {};
    EXPECT_ANY_THROW(s.getLoop());
}

TEST(SoundTest, GetDurationThrowsForUninitializedSound)
{
    Sound s {};
    EXPECT_ANY_THROW(s.getDuration());
}

TEST(SoundTest, GetPositionThrowsForUninitializedSound)
{
    Sound s {};
    EXPECT_ANY_THROW(s.getPosition());
}

TEST(SoundTest, SetInvalidVolumeNegative)
{
    Sound s {};
    s.load("assets/test.ogg");
    float const newVolume = -11.4f;
    EXPECT_THROW(s.setVolume(newVolume), std::invalid_argument);
}

TEST(SoundTest, SetInvalidVolumeAboveHundret)
{
    Sound s {};
    s.load("assets/test.ogg");
    float const newVolume = 666.555f;
    EXPECT_THROW(s.setVolume(newVolume), std::invalid_argument);
}

TEST(SoundTest, SetInvalidVolumeSlightlyBelowZero)
{
    Sound s {};
    s.load("assets/test.ogg");
    float const newVolume = 0.0f - std::numeric_limits<float>::epsilon();
    EXPECT_THROW(s.setVolume(newVolume), std::invalid_argument);
}

TEST(SoundTest, SetInvalidVolumeSlightlyAboveHundret)
{
    Sound s {};
    s.load("assets/test.ogg");
    float const newVolume = 100.1f;
    EXPECT_THROW(s.setVolume(newVolume), std::invalid_argument);
}

#endif
