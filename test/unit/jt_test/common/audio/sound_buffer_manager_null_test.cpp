#include <audio/sound_buffer_manager/sound_buffer_manager_null.hpp>
#include <oalpp/effects/utility/phase_flip.hpp>
#include <gtest/gtest.h>

TEST(SoundBufferManagerNullTest, ContainsNoBuffers)
{
    jt::null_objects::SoundBufferManagerNull manager;
    ASSERT_EQ(manager.getNumberOfBuffers(), 0u);
}

TEST(SoundBufferManagerNullTest, GetReturnsNoNullptr)
{
    jt::null_objects::SoundBufferManagerNull manager;
    ASSERT_NE(manager.get("abcd"), nullptr);
}

TEST(SoundBufferManagerNullTest, GetWithEffectReturnsNoNullptr)
{
    jt::null_objects::SoundBufferManagerNull manager;
    oalpp::effects::utility::PhaseFlip effect;
    ASSERT_NE(manager.get("abcd", "wet", effect), nullptr);
}

TEST(SoundBufferManagerNullTest, ContainsReturnsFalse)
{
    jt::null_objects::SoundBufferManagerNull manager;
    ASSERT_FALSE(manager.contains("xyzt"));
}
