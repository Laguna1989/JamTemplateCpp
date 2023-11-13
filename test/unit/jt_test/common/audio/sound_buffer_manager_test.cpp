#include <audio/sound_buffer_manager/sound_buffer_manager.hpp>
#include <oalpp/effects/utility/phase_flip.hpp>
#include <preload_helper.hpp>
#include <gtest/gtest.h>

TEST(SoundBufferManagerTest, InitiallyContainsNoBuffers)
{
    jt::SoundBufferManager manager {};
    ASSERT_EQ(manager.getNumberOfBuffers(), 0u);
}

TEST(SoundBufferManagerTest, ContainsBufferAfterGet)
{
    jt::SoundBufferManager manager {};
    manager.get("assets/intro.mp3");
    ASSERT_EQ(manager.getNumberOfBuffers(), 1u);
    ASSERT_TRUE(manager.contains("assets/intro.mp3"));
}

TEST(SoundBufferManagerTest, ContainsBufferAfterGetWithEffect)
{
    jt::SoundBufferManager manager {};
    oalpp::effects::utility::PhaseFlip effect;
    manager.get("assets/intro.mp3", "wet", effect);
    ASSERT_EQ(manager.getNumberOfBuffers(), 2u);
    ASSERT_TRUE(manager.contains("assets/intro.mp3#wet"));
}

TEST(SoundBufferManagerTest, Preload)
{
    jt::SoundBufferManager manager {};
    jt::PreloadHelper::preloadAllFrom(
        manager, "assets/test/unit/jt_test/mp3_for_preload", ".mp3", true);
    ASSERT_EQ(manager.getNumberOfBuffers(), 2u);
}

TEST(SoundBufferManagerTest, CallingGetTwiceReturnsSameBuffer)
{
    jt::SoundBufferManager manager {};
    auto const buffer0 = manager.get("assets/intro.mp3");
    auto const buffer1 = manager.get("assets/intro.mp3");
    ASSERT_EQ(buffer0, buffer1);
}

TEST(SoundBufferManagerTest, CallingGetWithEffectTwiceReturnsSameBuffer)
{
    jt::SoundBufferManager manager {};
    oalpp::effects::utility::PhaseFlip effect;
    auto const buffer0 = manager.get("assets/intro.mp3", "wet", effect);
    auto const buffer1 = manager.get("assets/intro.mp3", "wet", effect);
    ASSERT_EQ(buffer0, buffer1);
}
