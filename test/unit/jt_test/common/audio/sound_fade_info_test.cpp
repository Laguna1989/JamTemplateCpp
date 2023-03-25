#include <audio/fades/sound_fade_info.hpp>
#include <mocks/mock_sound.hpp>
#include <gtest/gtest.h>

TEST(SoundFadeInfoTest, isAliveReturnsTrueInitially)
{
    std::shared_ptr<MockSound> sound = std::make_shared<MockSound>();
    jt::SoundFadeInfo fi { sound, 0.5f, 1.0f, 0.0f };
    ASSERT_TRUE(fi.isAlive());
}
TEST(SoundFadeInfoTest, isAliveReturnsTrueAfterUpdateShorterThanFade)
{
    std::shared_ptr<MockSound> sound = std::make_shared<MockSound>();
    jt::SoundFadeInfo fi { sound, 0.5f, 1.0f, 0.0f };
    fi.update(0.2f);
    ASSERT_TRUE(fi.isAlive());
}

TEST(SoundFadeInfoTest, isAliveReturnsFalseAfterUpdateLongerThanFade)
{
    std::shared_ptr<MockSound> sound = std::make_shared<MockSound>();
    jt::SoundFadeInfo fi { sound, 0.5f, 1.0f, 0.0f };
    fi.update(5.0f);
    ASSERT_FALSE(fi.isAlive());
}

TEST(SoundFadeInfoTest, hasValidSoundReturnsTrueForValidSound)
{
    std::shared_ptr<MockSound> sound = std::make_shared<MockSound>();
    jt::SoundFadeInfo fi { sound, 0.5f, 1.0f, 0.0f };
    ASSERT_TRUE(fi.hasValidSound());
}

TEST(SoundFadeInfoTest, hasValidSoundReturnsFalseForDeletedSound)
{
    std::shared_ptr<MockSound> sound = std::make_shared<MockSound>();
    jt::SoundFadeInfo fi { sound, 0.5f, 1.0f, 0.0f };
    sound.reset();
    ASSERT_FALSE(fi.hasValidSound());
}

TEST(SoundFadeInfoTest, UpdateWithoutValidSoundDoesNotThrow)
{
    std::shared_ptr<MockSound> sound = std::make_shared<MockSound>();
    jt::SoundFadeInfo fi { sound, 0.5f, 1.0f, 0.0f };
    sound.reset();
    ASSERT_NO_THROW(fi.update(0.5f));
}
