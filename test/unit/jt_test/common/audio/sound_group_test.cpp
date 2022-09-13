#include <audio/audio_null.hpp>
#include <audio/sound_group.hpp>
#include <gtest/gtest.h>

TEST(SoundGroupTest, EmptySoundGroupContainsNoSound)
{
    jt::SoundGroup group {};
    ASSERT_EQ(group.size(), 0u);
}
