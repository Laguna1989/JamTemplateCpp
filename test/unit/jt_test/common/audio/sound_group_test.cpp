#include <audio/sound_group.hpp>
#include <audio/sound_null.hpp>
#include <gtest/gtest.h>

TEST(SoundGroupTest, EmptySoundGroupContainsNoSound)
{
    jt::SoundGroup const group {};
    ASSERT_EQ(group.size(), 0U);
}

TEST(SoundGroupTest, ContainsCorrectNumberOfElements)
{
    jt::SoundGroup group {};
    auto const expectedNumberOfElements = 5U;

    for (auto i = 0U; i != expectedNumberOfElements; ++i) {
        group.add(std::make_shared<jt::SoundNull>());
    }
    ASSERT_EQ(group.size(), expectedNumberOfElements);
}

TEST(SoundGroupTest, CanBeConstructedWithEmptyVectorOfSharedPointersToSoundInterface)
{
    std::vector<std::shared_ptr<jt::SoundInterface>> const sounds;
    jt::SoundGroup const group { sounds };

    ASSERT_EQ(group.size(), sounds.size());
}

TEST(SoundGroupTest, CanBeConstructedWithFullVectorOfSharedPointersToSoundInterface)
{
    std::vector<std::shared_ptr<jt::SoundInterface>> const sounds {
        std::make_shared<jt::SoundNull>()
    };
    jt::SoundGroup const group { sounds };

    ASSERT_EQ(group.size(), sounds.size());
}

TEST(SoundGroupTest, IsPlayingReturnsFalseForNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_FALSE(group.isPlaying());
}

TEST(SoundGroupTest, PlayOnEmptyGroupHasNoEffect)
{
    jt::SoundGroup group {};
    ASSERT_NO_THROW(group.play());
}

TEST(SoundGroupTest, PlayPlaysSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_NO_THROW(group.play());
}

TEST(SoundGroupTest, StopOnEmptyGroupHasNoEffect)
{
    jt::SoundGroup group {};
    ASSERT_NO_THROW(group.stop());
}

TEST(SoundGroupTest, StopStopsSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_NO_THROW(group.stop());
}

TEST(SoundGroupTest, PauseOnEmptyGroupHasNoEffect)
{
    jt::SoundGroup group {};
    ASSERT_NO_THROW(group.pause());
}

TEST(SoundGroupTest, PausePausesSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_NO_THROW(group.pause());
}

TEST(SoundGroupTest, VolumeIsZeroForEmptyGroup)
{
    jt::SoundGroup group {};
    ASSERT_EQ(group.getVolume(), 0.0f);
}

TEST(SoundGroupTest, VolumeOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_EQ(group.getVolume(), 0.0f);
}

TEST(SoundGroupTest, SetVolumeOnEmptyGroupHasNoEffect)
{
    jt::SoundGroup group {};
    ASSERT_NO_THROW(group.setVolume(1.0f));
}

TEST(SoundGroupTest, SetVolumeOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_NO_THROW(group.setVolume(0.5f));
}

TEST(SoundGroupTest, SetLoopOnEmptyGroupHasNoEffect)
{
    jt::SoundGroup group {};
    ASSERT_NO_THROW(group.setLoop(true));
}

TEST(SoundGroupTest, SetLoopOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_NO_THROW(group.setLoop(true));
}

TEST(SoundGroupTest, GetLoopOnEmptyGroup)
{
    jt::SoundGroup group {};
    ASSERT_FALSE(group.getLoop());
}

TEST(SoundGroupTest, GetLoopOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_FALSE(group.getLoop());
}

TEST(SoundGroupTest, DurationIsZeroForEmptyGroup)
{
    jt::SoundGroup group {};
    ASSERT_EQ(group.getDuration(), 0.0f);
}

TEST(SoundGroupTest, PositionIsZeroForEmptyGroup)
{
    jt::SoundGroup group {};
    ASSERT_EQ(group.getPosition(), 0.0f);
}

TEST(SoundGroupTest, SetBlendForEmptyGroupHasNoEffect)
{
    jt::SoundGroup group {};
    ASSERT_NO_THROW(group.setBlend(1.0f));
}
TEST(SoundGroupTest, SetBlendOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_NO_THROW(group.setBlend(0.5f));
}

TEST(SoundGroupTest, GetBlendOnEmptyGroup)
{
    jt::SoundGroup group {};

    ASSERT_EQ(group.getBlend(), 0.0f);
}

TEST(SoundGroupTest, GetBlendOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_EQ(group.getBlend(), 0.0f);
}

TEST(SoundGroupTest, SampleRateIsZeroForEmptyGroup)
{
    jt::SoundGroup group {};
    ASSERT_EQ(group.getSampleRate(), 0);
}

TEST(SoundGroupTest, SampleRateOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_EQ(group.getSampleRate(), 44100);
}

TEST(SoundGroupTest, Update)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_NO_THROW(group.update());
}

TEST(SoundGroupTest, SetPitchForEmptyGroupHasNoEffect)
{
    jt::SoundGroup group {};
    ASSERT_NO_THROW(group.setPitch(1.0f));
}

TEST(SoundGroupTest, SetPitchOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_NO_THROW(group.setPitch(0.5f));
}

TEST(SoundGroupTest, PitchIsOneForEmptyGroup)
{
    jt::SoundGroup group {};
    ASSERT_EQ(group.getPitch(), 1.0f);
}

TEST(SoundGroupTest, GetPitchOnNullSound)
{
    jt::SoundGroup group {};

    auto const snd = std::make_shared<jt::SoundNull>();
    group.add(snd);

    ASSERT_EQ(group.getPitch(), 1.0f);
}
