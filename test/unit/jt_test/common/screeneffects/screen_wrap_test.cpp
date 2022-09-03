#include <backend_setup.hpp>
#include <screeneffects/screen_wrap.hpp>
#include <shape.hpp>
#include <gtest/gtest.h>

class ScreenWrapTest : public ::testing::Test {
protected:
    std::shared_ptr<jt::Shape> drawable;
    jt::TextureManagerInterface& tm { getTextureManager() };
    jt::Vector2f screenSize { 800.0f, 600.0f };
    void SetUp() override
    {
        drawable = std::make_shared<jt::Shape>();
        drawable->makeRect(jt::Vector2f { 10.0f, 10.0f }, tm);
        drawable->setScreenSizeHint(screenSize);
    }
    void TearDown() override
    {
        // reset static cam offset just to make sure
        jt::DrawableImpl::setCamOffset(jt::Vector2f { 0.0f, 0.0f });
    }
};

class ScreenWrapBecauseOfWorldPositionTestFixture
    : public ScreenWrapTest,
      public ::testing::WithParamInterface<std::tuple<jt::Vector2f, jt::Vector2f, float>> { };

TEST_P(ScreenWrapBecauseOfWorldPositionTestFixture, WraptTest)
{
    auto const initialPosition = std::get<0>(GetParam());
    auto const expectedPositionAfterWrap = std::get<1>(GetParam());
    auto const margin = std::get<2>(GetParam());
    drawable->setPosition(initialPosition);
    jt::wrapOnScreen(*drawable.get(), margin);
    EXPECT_EQ(drawable->getPosition(), expectedPositionAfterWrap);
}

INSTANTIATE_TEST_SUITE_P(ScreenWrapBecauseOfWorldPositionTest,
    ScreenWrapBecauseOfWorldPositionTestFixture,
    ::testing::Values(
        // inside, no wrap
        std::make_tuple(jt::Vector2f { 400.0f, 300.0f }, jt::Vector2f { 400.0f, 300.0f }, 0.0f),
        // inside, no wrap
        std::make_tuple(jt::Vector2f { 150.0f, 500.0f }, jt::Vector2f { 150.0f, 500.0f }, 0.0f),
        // inside, no wrap, with margin
        std::make_tuple(jt::Vector2f { 400.0f, 300.0f }, jt::Vector2f { 400.0f, 300.0f }, 50.0f),
        // inside, no wrap, with margin
        std::make_tuple(jt::Vector2f { 10.0f, 500.0f }, jt::Vector2f { 10.0f, 500.0f }, 10.0f),
        // left out
        std::make_tuple(jt::Vector2f { -50.0f, 200.0f }, jt::Vector2f { 750.0f, 200.0f }, 0.0f),
        // left out but not wrapped due to margin
        std::make_tuple(jt::Vector2f { -5.0f, 200.0f }, jt::Vector2f { -5.0f, 200.0f }, 10.0f),
        // right out
        std::make_tuple(jt::Vector2f { 810.0f, 200.0f }, jt::Vector2f { 10.0f, 200.0f }, 0.0f),
        // right out but not wrapped due to margin
        std::make_tuple(jt::Vector2f { 805.0f, 200.0f }, jt::Vector2f { 805.0f, 200.0f }, 10.0f),
        // top out
        std::make_tuple(jt::Vector2f { 50.0f, -5.0f }, jt::Vector2f { 50.0f, 595.0f }, 0.0f),
        // top out but not wrapped due to margin
        std::make_tuple(jt::Vector2f { 50.0f, -5.0f }, jt::Vector2f { 50.0f, -5.0f }, 10.0f),
        // bottom out
        std::make_tuple(jt::Vector2f { 50.0f, 620.0f }, jt::Vector2f { 50.0f, 20.0f }, 0.0f),
        // bottom out but not wrapped due to margin
        std::make_tuple(jt::Vector2f { 50.0f, 610.0f }, jt::Vector2f { 50.0f, 610.0f }, 20.0f)));

class ScreenWrapBecauseOfCamPositionTestFixture
    : public ScreenWrapTest,
      public ::testing::WithParamInterface<std::tuple<jt::Vector2f, jt::Vector2f, float>> { };

TEST_P(ScreenWrapBecauseOfCamPositionTestFixture, WrapTest)
{
    auto const camPosition = std::get<0>(GetParam());
    auto const expectedPositionAfterWrap = std::get<1>(GetParam());
    auto const margin = std::get<2>(GetParam());
    jt::Vector2f const initialPosition { 10.0f, 20.0f };
    drawable->setPosition(initialPosition);
    jt::DrawableImpl::setCamOffset(camPosition);
    jt::wrapOnScreen(*drawable.get(), margin);
    EXPECT_EQ(drawable->getPosition(), expectedPositionAfterWrap);
}

TEST_P(ScreenWrapBecauseOfCamPositionTestFixture, WrapTestWithZeroScreenSizeDoesNothing)
{
    auto const camPosition = std::get<0>(GetParam());
    auto const margin = std::get<2>(GetParam());
    jt::Vector2f const initialPosition { 10.0f, 20.0f };
    drawable->setPosition(initialPosition);
    drawable->setScreenSizeHint({ 0.0f, 0.0f });
    jt::DrawableImpl::setCamOffset(camPosition);
    jt::wrapOnScreen(*drawable.get(), margin);
    EXPECT_EQ(drawable->getPosition(), initialPosition);
}

INSTANTIATE_TEST_SUITE_P(ScreenWrapBecauseOfCamPositionTest,
    ScreenWrapBecauseOfCamPositionTestFixture,
    ::testing::Values(
        // inside, no wrap
        std::make_tuple(jt::Vector2f { 0.0f, 0.0f }, jt::Vector2f { 10.0f, 20.0f }, 0.0f),
        // inside, no wrap
        std::make_tuple(jt::Vector2f { 100.0f, 200.0f }, jt::Vector2f { 10.0f, 20.0f }, 0.0f),
        // left out
        std::make_tuple(jt::Vector2f { -20.0f, 0.0f }, jt::Vector2f { 810.0f, 20.0f }, 0.0f),
        // right out
        std::make_tuple(jt::Vector2f { 800.0f, 0.0f }, jt::Vector2f { -790.0f, 20.0f }, 0.0f),
        // top out
        std::make_tuple(jt::Vector2f { 0.0f, -30.0f }, jt::Vector2f { 10.0f, 620.0f }, 0.0f),
        // bottom out
        std::make_tuple(jt::Vector2f { 0.0f, 600.0f }, jt::Vector2f { 10.0f, -580.0f }, 0.0f)));

class ScreenWrapWithCamFactorTestFixture
    : public ScreenWrapTest,
      public ::testing::WithParamInterface<std::tuple<jt::Vector2f, jt::Vector2f, float>> { };

TEST_P(ScreenWrapWithCamFactorTestFixture, WrapTest)
{
    auto const camPosition = std::get<0>(GetParam());
    auto const expectedPositionAfterWrap = std::get<1>(GetParam());
    auto const camFactor = std::get<2>(GetParam());
    jt::Vector2f const initialPosition { 10.0f, 20.0f };
    drawable->setPosition(initialPosition);
    drawable->setCamMovementFactor(camFactor);
    jt::DrawableImpl::setCamOffset(camPosition);
    jt::wrapOnScreen(*drawable.get(), 0.0f);
    EXPECT_EQ(drawable->getPosition(), expectedPositionAfterWrap);
}

INSTANTIATE_TEST_SUITE_P(ScreenWrapWithCamFactorTest, ScreenWrapWithCamFactorTestFixture,
    ::testing::Values(
        // inside, no wrap
        std::make_tuple(jt::Vector2f { 0.0f, 0.0f }, jt::Vector2f { 10.0f, 20.0f }, 1.0f),
        // inside, no wrap
        std::make_tuple(jt::Vector2f { 100.0f, 200.0f }, jt::Vector2f { 10.0f, 20.0f }, 1.0f),
        // outside, no wrap because of CamFactor 0
        std::make_tuple(jt::Vector2f { -20.0f, 0.0f }, jt::Vector2f { 10.0f, 20.0f }, 0.0f),
        // no wrap because of low CamFactor
        std::make_tuple(jt::Vector2f { 800.0f, 0.0f }, jt::Vector2f { 10.0f, 20.0f }, 0.5f),
        // wrap because left out
        std::make_tuple(jt::Vector2f { 1600.0f, 0.0f }, jt::Vector2f { -790.0f, 20.0f }, 0.5f),
        // wrap because right out
        std::make_tuple(jt::Vector2f { -400.0f, 600.0f }, jt::Vector2f { 810.0f, 20.0f }, 0.1f)));

TEST_F(ScreenWrapTest, TestWrapScreenPositionAfterWrapWithCamFactor)
{
    jt::Vector2f const camPosition { -100.0f, 0.0f };
    jt::Vector2f const expectedScreenPositionAfterWrap { 750.0f, 0.0f };
    jt::Vector2f const expectedWorldPositionAfterWrap { 800.0f, 0.0f };
    float const camFactor = 0.5f;
    jt::Vector2f const initialPosition { 0.0f, 0.0f };
    drawable->setPosition(initialPosition);
    drawable->setCamMovementFactor(camFactor);
    jt::DrawableImpl::setCamOffset(camPosition);
    jt::wrapOnScreen(*drawable.get(), 0.0f);
    EXPECT_EQ(drawable->getScreenPosition(), expectedScreenPositionAfterWrap);
    EXPECT_EQ(drawable->getPosition(), expectedWorldPositionAfterWrap);
}
