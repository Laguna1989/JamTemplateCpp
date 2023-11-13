#include <audio/sound/sound_data_null.hpp>
#include <gtest/gtest.h>

TEST(SoundDataNullTest, NumberOfChannelsReturn1)
{
    jt::null_objects::SoundDataNull data;
    ASSERT_EQ(data.getNumberOfChannels(), 1);
}

TEST(SoundDataNullTest, SampleRateReturns44100)
{
    jt::null_objects::SoundDataNull data;
    ASSERT_EQ(data.getSampleRate(), 44100);
}

TEST(SoundDataNullTest, SamplesIsEmptyVector)
{
    jt::null_objects::SoundDataNull data;
    ASSERT_TRUE(data.getSamples().empty());
}
