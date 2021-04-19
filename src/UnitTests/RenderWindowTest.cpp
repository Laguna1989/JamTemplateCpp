#include "RenderWindow.hpp"
#include <gtest/gtest.h>

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
