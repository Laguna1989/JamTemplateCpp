#include "render_window.hpp"
#include "render_window_null.hpp"
#include "sprite.hpp"
#include <gtest/gtest.h>
#include <stdexcept>
#include <utility>

class RenderWindowFactoryInterface {
public:
    virtual std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title)
        = 0;
};

class RenderWindowFactory : public RenderWindowFactoryInterface {
public:
    std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title) override
    {
        return std::make_shared<jt::RenderWindow>(width, height, title);
    }
};

class RenderWindowNullFactory : public RenderWindowFactoryInterface {
public:
    std::shared_ptr<jt::RenderWindowInterface> createRenderWindow(
        unsigned int width, unsigned int height, std::string const& title) override
    {
        return std::make_shared<jt::null_objects::RenderWindowNull>(width, height, title);
    }
};

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
    ASSERT_EQ(m_window->getSize().x(), w);
    ASSERT_EQ(m_window->getSize().y(), h);
}

TEST_P(RenderwindowCommonTestFixture, CheckForCloseDoesNotTerminate)
{
    ASSERT_NO_THROW(m_window->checkForClose());
}

TEST_P(RenderwindowCommonTestFixture, CreateRenderTargetReturnsValidTarget)
{
    ASSERT_NE(m_window->createRenderTarget(), nullptr);
}

TEST_P(RenderwindowCommonTestFixture, DrawValidSprite)
{
    auto spr = std::make_unique<jt::Sprite>();
    spr->loadSprite("assets/coin.png", { 0, 0, 16, 16 });
    m_window->draw(spr);
}

TEST_P(RenderwindowCommonTestFixture, DrawNullptrSprite)
{
    jt::RenderWindow rw { 100, 200, "test" };
    std::unique_ptr<jt::Sprite> spr { nullptr };
    ASSERT_THROW(m_window->draw(spr), std::invalid_argument);
}

TEST_P(RenderwindowCommonTestFixture, Display) { ASSERT_NO_THROW(m_window->display()); }

TEST_P(RenderwindowCommonTestFixture, GetMousePositionWithoutView)
{
    jt::Vector2 const expected { 0.0f, 0.0f };
    ASSERT_EQ(m_window->getMousePosition(), expected);
}

TEST_P(RenderwindowCommonTestFixture, GetMousePositionOnScreen)
{
    jt::Vector2 const expected { 0.0f, 0.0f };
    ASSERT_NE(m_window->getMousePositionScreen(1.0f), expected);
}

TEST_P(RenderwindowCommonTestFixture, MouseIsInvisibleAfterSet)
{
    m_window->setMouseCursorVisible(false);
    ASSERT_FALSE(m_window->getMouseCursorVisible());
}

INSTANTIATE_TEST_SUITE_P(RenderwindowCommonTest, RenderwindowCommonTestFixture,
    ::testing::Values(
        std::make_shared<RenderWindowFactory>(), std::make_shared<RenderWindowNullFactory>()));
