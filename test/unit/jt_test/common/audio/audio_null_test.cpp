#include <audio/audio/audio_null.hpp>
#include <gtest/gtest.h>

TEST(AudioNullTest, getContext)
{
    jt::null_objects::AudioNull audio;
    // TODO (Simon)
    //    ASSERT_NO_THROW(audio.getContext());
}

TEST(AudioNullTest, GetPermanentSoundReturnsNoNullptr)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NE(audio.getPermanentSound("bla"), nullptr);
}

TEST(AudioNullTest, AddTemporarySoundReturnsNoNullptr)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NE(audio.addTemporarySound("bla"), nullptr);
}

TEST(AudioNullTest, AddPermanentSoundReturnsNoNullptr)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NE(audio.addPermanentSound("bla", "bla"), nullptr);
}
