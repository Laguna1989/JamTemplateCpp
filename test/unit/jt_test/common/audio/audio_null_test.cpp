#include <audio/audio_null.hpp>
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

TEST(AudioNullTest, AddTemporarySoundGroupReturnsNoNullptr)
{
    jt::AudioNull audio;

    ASSERT_NE(audio.addTemporarySoundGroup({ nullptr, nullptr }), nullptr);
}

TEST(AudioNullTest, AddPermanentSoundReturnsNoNullptr)
{
    jt::AudioNull audio;
    ASSERT_NE(audio.addPermanentSound("bla", "bla"), nullptr);
}

class FakeEffect : public ::oalpp::effects::MonoEffectInterface {
public:
    std::vector<float> process(std::vector<float> const& /*unused*/) override { return { 1.0f }; }
};

TEST(AudioNullTest, AddPermanentSoundWithEffectReturnsNoNullptr)
{
    jt::AudioNull audio;
    FakeEffect effect;
    ASSERT_NE(audio.addPermanentSound("bla", "bla", effect), nullptr);
}

TEST(AudioNullTest, AddPermanentSoundWithLoopingEffectReturnsNoNullptr)
{
    jt::AudioNull audio;
    FakeEffect effect;
    ASSERT_NE(audio.addPermanentSound("bla0", "bla1", "bla2", effect), nullptr);
}

TEST(AudioNullTest, SoundPoolReturnsNoNullptr)
{
    jt::AudioNull audio;
    ASSERT_NE(audio.soundPool("bla", "blubb", 4), nullptr);
}

TEST(AudioNullTest, RemovePermanentSoundDoesNotThrow)
{
    jt::AudioNull audio;
    ASSERT_NO_THROW(audio.removePermanentSound("abcd"));
}
