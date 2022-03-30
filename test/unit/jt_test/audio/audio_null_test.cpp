#include "audio/audio_null.hpp"
#include <gtest/gtest.h>

TEST(AudioNullTest, GetPermanentSoundReturnsNoNullptr)
{
    jt::AudioNull audio;
    ASSERT_NE(audio.getPermanentSound("bla"), nullptr);
}

TEST(AudioNullTest, AddTemporarySoundReturnsNoNullptr)
{
    jt::AudioNull audio;
    ASSERT_NE(audio.addTemporarySound("bla"), nullptr);
}

TEST(AudioNullTest, AddPermanentSoundReturnsNoNullptr)
{
    jt::AudioNull audio;
    ASSERT_NE(audio.addPermanentSound("bla", "bla"), nullptr);
}

class FakeEffect : public ::oalpp::effects::MonoEffectInterface {
public:
    std::vector<float> process(std::vector<float> const& input) override { return { 1.0f }; }
};

TEST(AudioNullTest, AddPermanentSoundWithEffectReturnsNoNullptr)
{
    jt::AudioNull audio;
    FakeEffect effect;
    ASSERT_NE(audio.addPermanentSound("bla", "bla", effect), nullptr);
}
