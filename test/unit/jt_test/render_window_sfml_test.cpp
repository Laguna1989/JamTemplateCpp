#include "render_window.hpp"
#include "render_window_test.hpp"
#include <gtest/gtest.h>

class RenderwindowSFMLTestFixture
    : public ::testing::TestWithParam<std::shared_ptr<RenderWindowFactoryInterface>> {
protected:
    std::shared_ptr<jt::RenderWindowInterface> m_window;
    void SetUp() override { m_window = GetParam()->createRenderWindow(100, 200, "test"); }
};

TEST_P(RenderwindowSFMLTestFixture, GetMousePositionWithoutView)
{
    jt::Vector2f const expected { 0.0f, 0.0f };
    ASSERT_NE(m_window->getMousePosition(), expected);
}

TEST_P(RenderwindowSFMLTestFixture, CreateRenderTargetReturnsValidTarget)
{
    GetParam()->checkRenderTarget(m_window->createRenderTarget());
}

INSTANTIATE_TEST_SUITE_P(RenderwindowSFMLTest, RenderwindowSFMLTestFixture,
    ::testing::Values(
        std::make_shared<RenderWindowFactory>(), std::make_shared<RenderWindowNullFactory>()));
