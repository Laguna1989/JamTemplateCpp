#include <audio/audio/audio_impl.hpp>
#include <audio/sound/sound.hpp>
#include <gtest/gtest.h>
#include <thread>
#include <type_traits>

using jt::Sound;

class SoundTestWithLoadedSound : public ::testing::Test {
private:
protected:
    std::shared_ptr<jt::SoundInterface> m_sound;

    jt::AudioImpl audio;

    SoundTestWithLoadedSound()
    {
        m_sound = audio.addPermanentSound("test sound", "event:/test/unit/jt_test/test");
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
    audio.update(0.0f);
    EXPECT_NO_THROW(m_sound->setVolume(0.5f));
    audio.update(0.0f);
    EXPECT_NO_THROW(m_sound->setVolume(0.75f));
    audio.update(0.0f);
    EXPECT_NO_THROW(m_sound->setVolume(0.2f));
    audio.update(0.0f);
}
