#include <audio/sound.hpp>
#include <oalpp/sound_context.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <thread>
#include <type_traits>

using jt::Sound;

class SoundTestWithLoadedSound : public ::testing::Test {
private:
    oalpp::SoundContext ctx;

protected:
    std::unique_ptr<Sound> m_sound;
    SoundTestWithLoadedSound()
    {
        m_sound = std::make_unique<Sound>("assets/test/unit/jt_test/test.ogg");
        m_sound->setLoop(false);
        m_sound->setVolume(1.0f);
        m_sound->stop();
    }
};

TEST_F(SoundTestWithLoadedSound, DefaultVolume) { EXPECT_EQ(m_sound->getVolume(), 1.0f); }

TEST_F(SoundTestWithLoadedSound, GetVolumeAfterSetVolume)
{
    float const newVolume = 0.25f;
    m_sound->setVolume(newVolume);
    EXPECT_FLOAT_EQ(m_sound->getVolume(), newVolume);
}

TEST_F(SoundTestWithLoadedSound, SetVolumeZero)
{
    float const newVolume = 0.0f;
    m_sound->setVolume(newVolume);
    EXPECT_FLOAT_EQ(m_sound->getVolume(), newVolume);
}

TEST_F(SoundTestWithLoadedSound, SetVolumeOne)
{
    float const newVolume = 1.0f;
    m_sound->setVolume(newVolume);
    EXPECT_FLOAT_EQ(m_sound->getVolume(), newVolume);
}

TEST_F(SoundTestWithLoadedSound, GetBlendAfterSetBlend)
{
    float const newBlend = 0.25f;
    m_sound->setBlend(newBlend);
    EXPECT_FLOAT_EQ(m_sound->getBlend(), newBlend);
}

TEST_F(SoundTestWithLoadedSound, SetBlendZero)
{
    float const newBlend = 0.0f;
    m_sound->setBlend(newBlend);
    EXPECT_FLOAT_EQ(m_sound->getBlend(), newBlend);
}

TEST_F(SoundTestWithLoadedSound, SetBlendOne)
{
    float const newBlend = 1.0f;
    m_sound->setBlend(newBlend);
    EXPECT_FLOAT_EQ(m_sound->getBlend(), newBlend);
}

TEST_F(SoundTestWithLoadedSound, GetPitchAfterSetPitch)
{
    float const newPitch = 0.25f;
    m_sound->setPitch(newPitch);
    EXPECT_FLOAT_EQ(m_sound->getPitch(), newPitch);
}

TEST_F(SoundTestWithLoadedSound, SetPitchAboveZero)
{
    float const newPitch = 0.1f;
    m_sound->setPitch(newPitch);
    EXPECT_FLOAT_EQ(m_sound->getPitch(), newPitch);
}

TEST_F(SoundTestWithLoadedSound, SetPitchAboveOne)
{
    float const newPitch = 5.0f;
    m_sound->setPitch(newPitch);
    EXPECT_FLOAT_EQ(m_sound->getPitch(), newPitch);
}

TEST_F(SoundTestWithLoadedSound, StopDoesNothingWhenNotPlaying)
{
    m_sound->stop();
    EXPECT_FALSE(m_sound->isPlaying());
}

TEST_F(SoundTestWithLoadedSound, StopPlayingSound)
{
    m_sound->play();
    m_sound->stop();
    EXPECT_FALSE(m_sound->isPlaying());
}

TEST_F(SoundTestWithLoadedSound, GetLoopReturnsFalseOnDefault) { EXPECT_FALSE(m_sound->getLoop()); }

TEST_F(SoundTestWithLoadedSound, GetLoopAfterSetLoop)
{
    m_sound->setLoop(true);
    EXPECT_TRUE(m_sound->getLoop());
}

TEST_F(SoundTestWithLoadedSound, GetPositionAfterLoad)
{
    EXPECT_FLOAT_EQ(m_sound->getPosition(), 0.0f);
}

TEST_F(SoundTestWithLoadedSound, PlayTwice)
{
    m_sound->play();
    EXPECT_NO_THROW(m_sound->play());
}

TEST_F(SoundTestWithLoadedSound, StopTwice)
{
    m_sound->play();
    m_sound->stop();
    EXPECT_NO_THROW(m_sound->stop());
}

TEST_F(SoundTestWithLoadedSound, PlayAfterStop)
{
    m_sound->play();
    m_sound->stop();
    EXPECT_NO_THROW(m_sound->play());
}

TEST_F(SoundTestWithLoadedSound, Pause)
{
    m_sound->play();
    EXPECT_NO_THROW(m_sound->pause());
}

TEST_F(SoundTestWithLoadedSound, PauseTwice)
{
    m_sound->play();
    m_sound->pause();
    EXPECT_NO_THROW(m_sound->pause());
}

TEST_F(SoundTestWithLoadedSound, SetVolumeWhilePlaying)
{
    EXPECT_NO_THROW(m_sound->play());
    ASSERT_TRUE(m_sound->isPlaying());
    EXPECT_NO_THROW(m_sound->setVolume(0.5f));
    EXPECT_NO_THROW(m_sound->setVolume(0.75f));
    EXPECT_NO_THROW(m_sound->setVolume(0.2f));
}

TEST_F(SoundTestWithLoadedSound, UpdateDoesNotThrow) { ASSERT_NO_THROW(m_sound->update()); }

TEST_F(SoundTestWithLoadedSound, GetSampleRateReturnsExpectedValue)
{
    ASSERT_EQ(m_sound->getSampleRate(), 44100);
}

#ifndef JT_ENABLE_WEB

TEST_F(SoundTestWithLoadedSound, GetPositionAfterPlay)
{
    m_sound->play();
    // note: play will happen in another thread, so in order to progress the
    // position, this test needs to sleep a bit.
    std::this_thread::sleep_for(std::chrono::milliseconds { 100U });
    EXPECT_NE(m_sound->getPosition(), 0.0f);
}
TEST_F(SoundTestWithLoadedSound, GetDurationReturnsExpectedValue)
{
    auto const d = m_sound->getDuration();
    float const expected { 0.262721002f };
    EXPECT_FLOAT_EQ(d, expected);
}

TEST_F(SoundTestWithLoadedSound, SetBlendBelowZeroRaisesException)
{
    float const newBlend = -0.1f;
    ASSERT_THROW(m_sound->setBlend(newBlend), std::invalid_argument);
    EXPECT_FLOAT_EQ(m_sound->getBlend(), 0.0f);
}
TEST_F(SoundTestWithLoadedSound, SetBlendAboveOneRaisesException)
{
    float const newBlend = 1.1f;
    ASSERT_THROW(m_sound->setBlend(newBlend), std::invalid_argument);
    EXPECT_FLOAT_EQ(m_sound->getBlend(), 0.0f);
}
TEST_F(SoundTestWithLoadedSound, SetPitchToZeroRaisesException)
{
    float const newPitch = -0.0f;
    ASSERT_THROW(m_sound->setPitch(newPitch), std::invalid_argument);
    EXPECT_FLOAT_EQ(m_sound->getPitch(), 1.0f);
}
#endif
