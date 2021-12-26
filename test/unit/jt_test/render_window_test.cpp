#include "render_window_test.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "texture_manager_impl.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>

class RenderwindowCommonTestFixture
    : public ::testing::TestWithParam<std::shared_ptr<RenderWindowFactoryInterface>> {
protected:
    std::shared_ptr<jt::RenderWindowInterface> m_window;
    void SetUp() override { m_window = GetParam()->createRenderWindow(100, 200, "test"); }
};

TEST_P(RenderwindowCommonTestFixture, IsOpenByDefault) { ASSERT_TRUE(m_window->isOpen()); }

TEST_P(RenderwindowCommonTestFixture, MouseIsVisibleByDefault)
{
    ASSERT_TRUE(m_window->getMouseCursorVisible());
}

TEST_P(RenderwindowCommonTestFixture, SizeIsAsSet)
{
    auto const w = 500;
    auto const h = 300;
    m_window = GetParam()->createRenderWindow(w, h, "abcd");
    ASSERT_EQ(m_window->getSize().x, w);
    ASSERT_EQ(m_window->getSize().y, h);
}

TEST_P(RenderwindowCommonTestFixture, CheckForCloseDoesNotTerminate)
{
    ASSERT_NO_THROW(m_window->checkForClose());
}

TEST_P(RenderwindowCommonTestFixture, DrawValidSprite)
{
    auto spr = std::make_unique<jt::Sprite>(
        "assets/coin.png", jt::Recti { 0, 0, 16, 16 }, getTextureManager());
    m_window->draw(spr);
}

TEST_P(RenderwindowCommonTestFixture, DrawNullptrSprite)
{
    jt::RenderWindow rw { 100, 200, "test" };
    std::unique_ptr<jt::Sprite> spr { nullptr };
    ASSERT_THROW(m_window->draw(spr), std::invalid_argument);
}

TEST_P(RenderwindowCommonTestFixture, Display) { ASSERT_NO_THROW(m_window->display()); }

TEST_P(RenderwindowCommonTestFixture, MouseIsInvisibleAfterSet)
{
    m_window->setMouseCursorVisible(false);
    ASSERT_FALSE(m_window->getMouseCursorVisible());
}

INSTANTIATE_TEST_SUITE_P(RenderwindowCommonTest, RenderwindowCommonTestFixture,
    ::testing::Values(
        std::make_shared<RenderWindowFactory>(), std::make_shared<RenderWindowNullFactory>()));
