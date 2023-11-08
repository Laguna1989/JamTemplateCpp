#include "animation.hpp"
#include "backend_setup.hpp"
#include "texture_manager_impl.hpp"
#include "gtest/gtest.h"
#include <stdexcept>
#include <type_traits>

TEST(AnimationTest, IsDefaultConstructible)
{
    ASSERT_TRUE(std::is_default_constructible<jt::Animation>::value);
}

class AnimationTestFixture : public ::testing::Test {
public:
    jt::TextureManagerInterface& tm { getTextureManager() };
    jt::Animation a;

    void SetUp() override { tm = getTextureManager(); }
};

TEST_F(AnimationTestFixture, AddAnimationWithEmptyNameRaisesInvalidArgumentException)
{
    ASSERT_THROW(
        a.add("assets/test/unit/jt_test/coin.png", "", { 16, 16 }, { 0, 1, 2, 3 }, 1.0f, tm),
        std::invalid_argument);
}

TEST_F(AnimationTestFixture, AddAnimationWithEmptyFrameIndicesRaisesInvalidArgumentException)
{
    ASSERT_THROW(a.add("assets/test/unit/jt_test/coin.png", "", { 16, 16 }, {}, 1.0f, tm),
        std::invalid_argument);
}

TEST_F(AnimationTestFixture, AddAnimationWithEmptyFrameTimesRaisesInvalidArgumentException)
{
    ASSERT_THROW(a.add("assets/test/unit/jt_test/coin.png", "", { 16, 16 }, { 1, 2, 3 }, {}, tm),
        std::invalid_argument);
}

TEST_F(AnimationTestFixture,
    AddAnimationWithDifferentFrameTimesAndFrameIndicesRaisesInvalidArgumentException)
{
    ASSERT_THROW(
        a.add("assets/test/unit/jt_test/coin.png", "", { 16, 16 }, { 1, 2, 3 }, { 0.1f, 0.2f }, tm),
        std::invalid_argument);
}

TEST_F(
    AnimationTestFixture, AddAnimationWithDifferentNumberOfFrameTimesRaisesInvalidArgumentException)
{
    ASSERT_THROW(
        a.add("assets/test/unit/jt_test/coin.png", "", { 16, 16 }, { 1, 2, 3 }, { 0.5f }, tm),
        std::invalid_argument);
}

TEST_F(AnimationTestFixture, AddAnimationWithNegativeTimeRaisesInvalidArgumentException)
{
    ASSERT_THROW(
        a.add("assets/test/unit/jt_test/coin.png", "test", { 16, 16 }, { 0, 1, 2, 3 }, -0.5f, tm),
        std::invalid_argument);
}

TEST_F(AnimationTestFixture, SetLoopingOnNonExistingAnimationRaisesException)
{
    ASSERT_THROW(a.setLooping("idle", false), std::invalid_argument);
}

TEST_F(AnimationTestFixture, InitialCurrentAnimationNameForDefaultConstructedAnimation)
{
    jt::Animation a {};
    ASSERT_EQ(a.getCurrentAnimationName(), "");
}

TEST_F(AnimationTestFixture, UpdateWithoutPlayDoesNotRaiseException)
{
    jt::Animation a {};
    ASSERT_NO_THROW(a.update(0.25f));
}

TEST_F(AnimationTestFixture, DrawWithoutPlayDoesNotRaiseException)
{
    jt::Animation a {};
    ASSERT_NO_THROW(a.draw(std::shared_ptr<jt::RenderTargetInterface> { nullptr }));
}

TEST_F(AnimationTestFixture, AddWithEmptyFrameTimesRaisesException)
{
    jt::Animation a {};
    ASSERT_THROW(
        a.add("abc", "def", jt::Vector2u { 8u, 8u }, { 0u, 1u }, {}, tm), std::invalid_argument);
}

TEST_F(AnimationTestFixture, AddWithWrongSizeFrameTimesRaisesException)
{
    jt::Animation a {};
    ASSERT_THROW(a.add("abc", "def", jt::Vector2u { 8u, 8u }, { 0u, 1u }, { 0.25f }, tm),
        std::invalid_argument);
}

TEST_F(AnimationTestFixture, GetAllAvailableAnimationsNamesReturnsEmptyVectorByDefault)
{
    jt::Animation a {};
    auto const animationNames = a.getAllAvailableAnimationNames();
    ASSERT_EQ(animationNames.size(), 0u);
}

TEST_F(AnimationTestFixture, GetRandomAnimationNameRaisesExceptionForDefaultAnimtaion)
{
    jt::Animation a {};
    ASSERT_THROW(a.getRandomAnimationName(), std::invalid_argument);
}

TEST_F(AnimationTestFixture, LoadFromJsonWithFileTypeThatIsNotJson)
{
    jt::Animation a {};
    ASSERT_THROW(a.loadFromJson("assets/Pilz.png", tm), std::invalid_argument);
}

#ifdef USE_SFML
TEST_F(AnimationTestFixture, LoadFromJson)
{
    jt::Animation a {};
    a.loadFromJson("assets/test/unit/jt_test/pilz_small.json", tm);
    a.play("Idle");

    ASSERT_EQ(a.getGlobalBounds().left, 0);
    ASSERT_EQ(a.getGlobalBounds().top, 0);
    ASSERT_EQ(a.getGlobalBounds().width, 16);
    ASSERT_EQ(a.getGlobalBounds().height, 16);

    auto const animationNames = a.getAllAvailableAnimationNames();
    ASSERT_EQ(animationNames.size(), 3u);
}
#endif

TEST_F(AnimationTestFixture, LoadFromAseprite)
{
    jt::Animation a {};
    a.loadFromAseprite("assets/test/unit/jt_test/dino_salto.aseprite", tm);
    a.play("InAir");

    ASSERT_EQ(a.getGlobalBounds().left, 0);
    ASSERT_EQ(a.getGlobalBounds().top, 0);
    ASSERT_EQ(a.getGlobalBounds().width, 24);
    ASSERT_EQ(a.getGlobalBounds().height, 18);

    auto const animationNames = a.getAllAvailableAnimationNames();
    ASSERT_EQ(animationNames.size(), 1u);
}

class AnimationTestWithAnimation : public ::testing::Test {
protected:
    jt::TextureManagerInterface& tm { getTextureManager() };
    jt::Animation a;

    void SetUp() override { addAnimationWithFrameIndices(); }

    void addAnimationWithFrameIndices(std::vector<unsigned int> frameIndices = { 0, 1, 2, 3, 4 })
    {
        a.add("assets/test/unit/jt_test/coin.png", "idle", { 16, 16 }, frameIndices, 1.0f, tm);
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
    a.add("assets/test/unit/jt_test/coin.png", "idle", { 16, 16 }, { 0 }, 1.0f, tm);
    ASSERT_TRUE(a.hasAnimation("idle"));
}

TEST_F(AnimationTestWithAnimation, GetColorWithoutPlayWillRaisInvalidArgument)
{
    ASSERT_THROW(a.getColor(), std::invalid_argument);
}

TEST_F(AnimationTestWithAnimation, PlayInvalidAnimationWillRaiseInvalidArgument)
{
    ASSERT_NO_THROW(a.play("test1234_invalid"));
}

TEST_F(AnimationTestWithAnimation, IsLoopingByDefault)
{
    ASSERT_TRUE(a.getCurrentAnimationIsLooping());
}

TEST_F(AnimationTestWithAnimation, IsLoopingForIsTrueByDefault)
{
    addAnimationWithFrameIndices();
    ASSERT_TRUE(a.getIsLoopingFor("idle"));
}

TEST_F(AnimationTestWithAnimation, IsLoopingForRaisesExceptionForInvalidName)
{
    ASSERT_THROW(a.getIsLoopingFor("blarz"), std::invalid_argument);
}

TEST_F(AnimationTestWithAnimation, IsLoopingAfterSetLoopingAll)
{
    addAnimationWithFrameIndices();
    a.setLoopingAll(false);
    ASSERT_FALSE(a.getIsLoopingFor("idle"));
}

TEST_F(AnimationTestWithAnimation, IsLoopingAfterPlay)
{
    addAnimationWithFrameIndices();
    a.play("idle");
    ASSERT_TRUE(a.getCurrentAnimationIsLooping());
}

TEST_F(AnimationTestWithAnimation, IsNotLoopingAfterSetLooping)
{
    a.play("idle");
    a.setLooping("idle", false);
    ASSERT_FALSE(a.getCurrentAnimationIsLooping());
}

TEST_F(AnimationTestWithAnimation, SetFrameTimes)
{
    a.play("idle");
    auto const numberOfFrames = a.getNumberOfFramesInCurrentAnimation();
    auto const expectedFrameTime = 2.45f;
    std::vector<float> frameTimes(numberOfFrames, expectedFrameTime);

    a.setFrameTimes("idle", frameTimes);
    ASSERT_EQ(a.getCurrentAnimationSingleFrameTime(), expectedFrameTime);
}

TEST_F(AnimationTestWithAnimation, SetFrameTimesWithInvalidAnimation)
{
    ASSERT_THROW(a.setFrameTimes("idle5", {}), std::invalid_argument);
}

TEST_F(AnimationTestWithAnimation, SetFrameTimesWithInvalidVectorSize)
{
    ASSERT_THROW(a.setFrameTimes("idle", { 1.23f }), std::invalid_argument);
}

TEST_F(AnimationTestWithAnimation, GetTotalTimeForReturnsValidTime)
{
    ASSERT_EQ(a.getAnimTotalTimeFor("idle"), 5.0f);
}

TEST_F(AnimationTestWithAnimation, GetTotalTimeRaisesExceptionForInvalidName)
{
    ASSERT_THROW(a.getAnimTotalTimeFor("BLARZ"), std::invalid_argument);
}

TEST_F(AnimationTestWithAnimation, GetRandomAnimationNameReturnsCorrectName)
{
    ASSERT_EQ(a.getRandomAnimationName(), "idle");
}

class AnimationPlayingTest : public ::testing::Test {
protected:
    jt::TextureManagerInterface& tm { getTextureManager() };
    jt::Animation a;

    void SetUp() override
    {
        a.add("assets/test/unit/jt_test/coin.png", "idle", { 16, 16 }, { 0, 1, 2, 3, 4 }, 1.0f, tm);
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
    a.draw(std::shared_ptr<jt::RenderTargetInterface> { nullptr });
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
    a.setLooping("idle", false);
    a.update(5.1f);
    ASSERT_EQ(a.getCurrentAnimationFrameIndex(), 4);
}

TEST_F(AnimationPlayingTest, AnimationPlaybackSpeed)
{
    auto const expectedValue = 0.5f;
    a.setAnimationSpeedFactor(expectedValue);
    ASSERT_EQ(a.getAnimationSpeedFactor(), expectedValue);
}
