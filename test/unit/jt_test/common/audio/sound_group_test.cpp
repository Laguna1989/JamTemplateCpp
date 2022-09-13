#include <audio/sound_group.hpp>
#include <audio/sound_null.hpp>
#include <gtest/gtest.h>

TEST(SoundGroupTest, EmptySoundGroupContainsNoSound)
{
    jt::SoundGroup const group {};
    ASSERT_EQ(group.size(), 0U);
}

TEST(SoundGroupTest, SoundGroupContainsCorrectNumberOfElements)
{
    jt::SoundGroup group {};
    auto const expectedNumberOfElements = 5U;

    for (auto i = 0U; i != expectedNumberOfElements; ++i) {
        group.add(std::make_shared<jt::SoundNull>());
    }
    ASSERT_EQ(group.size(), expectedNumberOfElements);
}

TEST(SoundGroupTest, SoundGroupCanBeConstructedWithVectorOfSharedPointersToSoundInterface)
{
    std::vector<std::shared_ptr<jt::SoundInterface>> sounds;
    jt::SoundGroup const group { sounds };

    ASSERT_EQ(group.size(), sounds.size());
}
