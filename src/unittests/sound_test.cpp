#include "sound.hpp"
#include <gtest/gtest.h>
#include <limits>
#include <thread>
#include <type_traits>

using jt::Sound;

void init() { }

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

// as loading of sound files is quite slow, this text fixture is speeding things up with static
// initialization.
class SoundTestWithLoadedSound : public ::testing::Test {
private:
    inline static bool m_initialized { false };

protected:
    inline static Sound m_sound;
    SoundTestWithLoadedSound() { initializeSound(); }
    void initializeSound()
    {
        init();
        if (!m_initialized) {
            m_initialized = true;
            m_sound.load("assets/test.ogg");
        }
        m_sound.setLoop(false);
        m_sound.setVolume(100);
        m_sound.stop();
    }
};

TEST_F(SoundTestWithLoadedSound, DefaultVolume) { EXPECT_EQ(m_sound.getVolume(), 100.0f); }

TEST_F(SoundTestWithLoadedSound, GetVolumeAfterSetVolume)
{
    float const newVolume = 25.245f;
    m_sound.setVolume(newVolume);
    EXPECT_FLOAT_EQ(m_sound.getVolume(), newVolume);
}

TEST_F(SoundTestWithLoadedSound, SetVolumeZero)
{
    float const newVolume = 0.0f;
    m_sound.setVolume(newVolume);
    EXPECT_FLOAT_EQ(m_sound.getVolume(), newVolume);
}

TEST_F(SoundTestWithLoadedSound, SetVolumeHundret)
{
    float const newVolume = 100.0f;
    m_sound.setVolume(newVolume);
    EXPECT_FLOAT_EQ(m_sound.getVolume(), newVolume);
}

TEST_F(SoundTestWithLoadedSound, StopDoesNothingWhenNotPlaying)
{
    m_sound.stop();
    EXPECT_FALSE(m_sound.isPlaying());
}

TEST_F(SoundTestWithLoadedSound, StopPlayingSound)
{
    m_sound.play();
    m_sound.stop();
    EXPECT_FALSE(m_sound.isPlaying());
}

TEST_F(SoundTestWithLoadedSound, GetLoopReturnsFalseOnDefault) { EXPECT_FALSE(m_sound.getLoop()); }

TEST_F(SoundTestWithLoadedSound, GetLoopAfterSetLoop)
{
    m_sound.setLoop(true);
    EXPECT_TRUE(m_sound.getLoop());
}

TEST_F(SoundTestWithLoadedSound, GetPositionAfterLoad)
{
    EXPECT_FLOAT_EQ(m_sound.getPosition(), 0.0f);
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

TEST_F(SoundTestWithLoadedSound, PlayTwice)
{
    m_sound.play();
    EXPECT_NO_THROW(m_sound.play());
}

TEST_F(SoundTestWithLoadedSound, StopTwice)
{
    m_sound.play();
    m_sound.stop();
    EXPECT_NO_THROW(m_sound.stop());
}

TEST_F(SoundTestWithLoadedSound, PlayAfterStop)
{
    m_sound.play();
    m_sound.stop();
    EXPECT_NO_THROW(m_sound.play());
}

TEST_F(SoundTestWithLoadedSound, SetVolumeWhilePlaying)
{
    EXPECT_NO_THROW(m_sound.play());
    ASSERT_TRUE(m_sound.isPlaying());
    EXPECT_NO_THROW(m_sound.setVolume(55.5f));
    EXPECT_NO_THROW(m_sound.setVolume(2.5f));
    EXPECT_NO_THROW(m_sound.setVolume(100.0f));
}

#ifndef ENABLE_WEB

TEST_F(SoundTestWithLoadedSound, GetPositionAfterPlay)
{
    m_sound.play();
    // note: play will happen in another thread, so in order to progress the
    // position, this test needs to sleep a bit.
    std::this_thread::sleep_for(std::chrono::milliseconds { 100U });
    EXPECT_NE(m_sound.getPosition(), 0.0f);
}
TEST_F(SoundTestWithLoadedSound, GetDurationReturnsExpectedValue)
{
    auto const d = m_sound.getDuration();
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
