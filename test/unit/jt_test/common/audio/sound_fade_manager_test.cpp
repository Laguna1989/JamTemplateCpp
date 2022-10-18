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
