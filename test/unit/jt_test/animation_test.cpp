#include "animation.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <type_traits>

TEST(AnimationTest, IsDefaultConstructible)
{
    ASSERT_TRUE(std::is_default_constructible<jt::Animation>::value);
}

TEST(AnimationTest, AddAnimationWithEmptyNameRaisesInvalidArgumentException)
{
    jt::Animation a;
    ASSERT_THROW(
        a.add("assets/coin.png", "", { 16, 16 }, { 0, 1, 2, 3 }, 1.0f), std::invalid_argument);
}

TEST(AnimationTest, AddAnimationWithEmptyFrameIndicesRaisesInvalidArgumentException)
{
    jt::Animation a;
    ASSERT_THROW(a.add("assets/coin.png", "", { 16, 16 }, {}, 1.0f), std::invalid_argument);
}

TEST(AnimationTest, AddAnimationWithNegativeTimeRaisesInvalidArgumentException)
{
    jt::Animation a;
    ASSERT_THROW(
        a.add("assets/coin.png", "test", { 16, 16 }, { 0, 1, 2, 3 }, -0.5f), std::invalid_argument);
}

TEST(AnimationTest, InitialCurrentAnimationName)
{
    jt::Animation a {};
    ASSERT_EQ(a.getCurrentAnimationName(), "");
}

TEST(AnimationTest, UpdateWithoutPlayDoesNotRaiseException)
{
    jt::Animation a {};
    ASSERT_NO_THROW(a.update(0.25f));
}
TEST(AnimationTest, DrawWithoutPlayDoesNotRaiseException)
{
    jt::Animation a {};
    ASSERT_NO_THROW(a.draw(nullptr));
}

class AnimationTestWithAnimation : public ::testing::Test {
protected:
    jt::Animation a;
    AnimationTestWithAnimation() { addAnimationWithFrameIndices(); }

    void addAnimationWithFrameIndices(std::vector<unsigned int> frameIndices = { 0, 1, 2, 3, 4 })
    {
        a.add("assets/coin.png", "idle", { 16, 16 }, frameIndices, 1.0f);
    }
};

TEST_F(AnimationTestWithAnimation, AddWillAddAnimation) { ASSERT_TRUE(a.hasAnimation("idle")); }

TEST_F(AnimationTestWithAnimation, AddWillAddAnimationWithSingleFrame)
{
    addAnimationWithFrameIndices({ 0 });
    ASSERT_TRUE(a.hasAnimation("idle"));
}

TEST_F(AnimationTestWithAnimation, OverwriteAnimation)
{
    a.add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f);
    ASSERT_TRUE(a.hasAnimation("idle"));
}

TEST_F(AnimationTestWithAnimation, GetColorWithoutPlayWillRaisInvalidArgument)
{
    ASSERT_THROW(a.getColor(), std::invalid_argument);
}

TEST_F(AnimationTestWithAnimation, PlayInvalidAnimationWillRaiseInvalidArgument)
{
    ASSERT_THROW(a.play("test1234_invalid"), std::invalid_argument);
}

TEST_F(AnimationTestWithAnimation, IsLoopingByDefault) { ASSERT_TRUE(a.getIsLooping()); }

TEST_F(AnimationTestWithAnimation, IsNotLoopingAfterSetLooping)
{
    a.setLooping(false);
    ASSERT_FALSE(a.getIsLooping());
}

class AnimationPlayingTest : public ::testing::Test {
protected:
    jt::Animation a;
    AnimationPlayingTest()
    {
        a.add("assets/coin.png", "idle", { 16, 16 }, { 0, 1, 2, 3, 4 }, 1.0f);
        a.play("idle");
    }
};

TEST_F(AnimationPlayingTest, NumberOfFrames)
{
    ASSERT_EQ(a.getNumberOfFramesInCurrentAnimation(), 5);
}

TEST_F(AnimationPlayingTest, SingleFrameTime)
{
    ASSERT_FLOAT_EQ(a.getCurrentAnimationSingleFrameTime(), 1.0f);
}

TEST_F(AnimationPlayingTest, TotalFrameTime) { ASSERT_FLOAT_EQ(a.getCurrentAnimTotalTime(), 5.0f); }

TEST_F(AnimationPlayingTest, UpdateSwitchesAnimationIndex) { a.update(10.0f); }

TEST_F(AnimationPlayingTest, CurrentAnimationNameAfterPlay)
{
    ASSERT_EQ(a.getCurrentAnimationName(), "idle");
}

// white box test for coverage
TEST_F(AnimationPlayingTest, AnimationCanBeFlashed)
{
    a.flash(1.0f);
    a.update(0.1f);
    a.draw(nullptr);
}

TEST_F(AnimationPlayingTest, AnimationStartsAtFrameZero)
{
    ASSERT_EQ(a.getCurrentAnimationFrameIndex(), 0);
}

TEST_F(AnimationPlayingTest, IndexIsZeroIfFirstFrameIsNotPassed)
{
    a.update(0.99f);
    ASSERT_EQ(a.getCurrentAnimationFrameIndex(), 0);
}

TEST_F(AnimationPlayingTest, IndexIsIncreasedAfterFrameTimePassed)
{
    a.update(1.01f);
    ASSERT_EQ(a.getCurrentAnimationFrameIndex(), 1);
}

TEST_F(AnimationPlayingTest, IndexIsIncreasedAfterFrameTimePassedInOneCall)
{
    a.update(2.01f);
    ASSERT_EQ(a.getCurrentAnimationFrameIndex(), 2);
}

TEST_F(AnimationPlayingTest, IndexIsIncreasedAfterFrameTimePassedTwoCalls)
{
    a.update(1.01f);
    a.update(1.01f);
    ASSERT_EQ(a.getCurrentAnimationFrameIndex(), 2);
}

TEST_F(AnimationPlayingTest, IndexIsWrappedAfterCompleteAnimationWhenLooping)
{
    a.update(5.1f);
    ASSERT_EQ(a.getCurrentAnimationFrameIndex(), 0);
}

TEST_F(AnimationPlayingTest, IndexIsNotWrappedAfterCompleteAnimationWhenNotLooping)
{
    a.setLooping(false);
    a.update(5.1f);
    ASSERT_EQ(a.getCurrentAnimationFrameIndex(), 4);
}
