#include <audio/audio/audio_null.hpp>
#include <gtest/gtest.h>

TEST(AudioNullTest, getContext)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NO_THROW(audio.getContext());
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

TEST(AudioNullTest, AddTemporarySoundGroupReturnsNoNullptr)
{
    jt::null_objects::AudioNull audio;

    ASSERT_NE(audio.addTemporarySoundGroup({ nullptr, nullptr }), nullptr);
}

TEST(AudioNullTest, AddPermanentSoundReturnsNoNullptr)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NE(audio.addPermanentSound("bla", "bla"), nullptr);
}

class FakeEffect : public ::oalpp::effects::MonoEffectInterface {
public:
    std::vector<float> process(std::vector<float> const& /*unused*/) override { return { 1.0f }; }
};

TEST(AudioNullTest, AddPermanentSoundWithEffectReturnsNoNullptr)
{
    jt::null_objects::AudioNull audio;
    FakeEffect effect;
    ASSERT_NE(audio.addPermanentSound("bla", "bla", effect), nullptr);
}

TEST(AudioNullTest, AddPermanentSoundWithLoopingEffectReturnsNoNullptr)
{
    jt::null_objects::AudioNull audio;
    FakeEffect effect;
    ASSERT_NE(audio.addPermanentSound("bla0", "bla1", "bla2", effect), nullptr);
}

TEST(AudioNullTest, SoundPoolReturnsNoNullptr)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NE(audio.soundPool("bla", "blubb", 4), nullptr);
}

TEST(AudioNullTest, RemovePermanentSoundDoesNotThrow)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NO_THROW(audio.removePermanentSound("abcd"));
}

TEST(AudioNullTest, FadesDoesNotThrow)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NO_THROW(audio.fades());
}

TEST(AudioNullTest, groupsDoesNotThrow)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NO_THROW(audio.groups());
}

TEST(AudioNullTest, soundBufferManagerDoesNotThrow)
{
    jt::null_objects::AudioNull audio;
    ASSERT_NO_THROW(audio.getSoundBufferManager());
}
