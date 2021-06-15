#include "render_window.hpp"
#include "sprite.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(RenderwindowTest, IsOpenByDefault)
{
    jt::RenderWindow const rw { 100, 200, "test" };
    EXPECT_TRUE(rw.isOpen());
}

TEST(RenderwindowTest, SizeIsAsSet)
{
    auto const w = 500;
    auto const h = 300;
    jt::RenderWindow const rw { w, h, "test" };
    EXPECT_EQ(rw.getSize().x(), w);
    EXPECT_EQ(rw.getSize().y(), h);
}

TEST(RenderwindowTest, CheckForCloseDoesNotTerminate)
{
    jt::RenderWindow rw { 100, 200, "test" };
    EXPECT_NO_THROW(rw.checkForClose());
}

TEST(RenderwindowTest, CreateRenderTargetReturnsValidTarget)
{
    jt::RenderWindow rw { 100, 200, "test" };
    EXPECT_NE(rw.createRenderTarget(), nullptr);
}

TEST(RenderwindowTest, DrawValidSprite)
{
    jt::RenderWindow rw { 100, 200, "test" };
    auto spr = std::make_shared<jt::Sprite>();
    spr->loadSprite("assets/coin.png", { 0, 0, 16, 16 });
    rw.draw(spr);
}

TEST(RenderwindowTest, DrawNullptrSprite)
{
    jt::RenderWindow rw { 100, 200, "test" };
    EXPECT_THROW(rw.draw(nullptr), std::invalid_argument);
}

TEST(RenderwindowTest, Display)
{
    jt::RenderWindow rw { 100, 200, "test" };
    rw.display();
}
