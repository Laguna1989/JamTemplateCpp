#include <audio/sound_fade_manager.hpp>
#include <mocks/mock_sound.hpp>
#include <gtest/gtest.h>

TEST(SoundFadeManagerTest, VolumeAfterCompleteFade)
{
    auto snd = std::make_shared<MockSound>();

    jt::SoundFadeManager fm;
    fm.volumeFade(snd, 1.0f, 1.0f, 0.0f);
    EXPECT_CALL(*snd, setVolume(0.0f));
    fm.update(1.0f);
}

TEST(SoundFadeManagerTest, VolumeAfterHalfFade)
{
    auto snd = std::make_shared<MockSound>();

    jt::SoundFadeManager fm;
    fm.volumeFade(snd, 1.0f, 1.0f, 0.0f);
    EXPECT_CALL(*snd, setVolume(0.5f));
    fm.update(0.5f);
}

TEST(SoundFadeManagerTest, InvalidSound)
{
    auto snd = std::make_shared<MockSound>();

    jt::SoundFadeManager fm;
    fm.volumeFade(snd, 1.0f, 1.0f, 0.0f);
    snd.reset();
    ASSERT_NO_THROW(fm.update(0.5f));
}

TEST(SoundFadeManagerTest, InitiallyNoFades)
{
    jt::SoundFadeManager fm;
    ASSERT_EQ(fm.size(), 0U);
}

TEST(SoundFadeManagerTest, SizeIsIncreasedByVolumeFade)
{
    jt::SoundFadeManager fm;
    ASSERT_EQ(fm.size(), 0U);

    auto snd = std::make_shared<MockSound>();
    fm.volumeFade(snd, 1.0f, 1.0f, 0.0f);
    ASSERT_EQ(fm.size(), 1U);
}

TEST(SoundFadeManagerTest, SizeIsDecreasedBySoundBeingDestroyed)
{
    jt::SoundFadeManager fm;
    ASSERT_EQ(fm.size(), 0U);

    auto snd = std::make_shared<MockSound>();
    fm.volumeFade(snd, 1.0f, 1.0f, 0.0f);
    ASSERT_EQ(fm.size(), 1U);

    snd.reset();

    fm.update(0.0f);
    ASSERT_EQ(fm.size(), 0U);
}

TEST(SoundFadeManagerTest, SizeIsDecreasedByFadeBeingCompleted)
{
    jt::SoundFadeManager fm;
    ASSERT_EQ(fm.size(), 0U);

    auto snd = std::make_shared<MockSound>();
    fm.volumeFade(snd, 1.0f, 1.0f, 0.0f);
    ASSERT_EQ(fm.size(), 1U);

    // sanity
    EXPECT_CALL(*snd, setVolume(0.0f));
    fm.update(2.0f);

    ASSERT_EQ(fm.size(), 0U);
}
