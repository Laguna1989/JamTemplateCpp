#include "../JamTemplate/Game.hpp"
#include "gtest/gtest.h"

using JamTemplate::Game;

TEST(GameTest, InitialValues)
{
    auto const windowSizeX = 100;
    auto const windowSizeY = 200;
    auto const zoom = 5.0f;
    Game g { windowSizeX, windowSizeY, zoom, "test" };

    EXPECT_NE(g.getRenderTarget(), nullptr);
    EXPECT_NE(g.getRenderWindow(), nullptr);
    EXPECT_NE(g.getView(), nullptr);

    EXPECT_EQ(g.getZoom(), zoom);

    EXPECT_NEAR(g.getRenderTarget()->getSize().x, windowSizeX / zoom, 0.001);
    EXPECT_NEAR(g.getRenderTarget()->getSize().y, windowSizeY / zoom, 0.001);

    // windows returns the full size of the window, while game ctor takes only the drawable area
    EXPECT_GE(g.getRenderWindow()->getSize().x, windowSizeX);
    EXPECT_GE(g.getRenderWindow()->getSize().y, windowSizeY);

    EXPECT_EQ(g.getCamOffset().x, 0);
    EXPECT_EQ(g.getCamOffset().y, 0);

    g.update(0.5f);
    EXPECT_EQ(g.getAge(), 0.5f);

    EXPECT_TRUE(g.isAlive());
    g.kill();
    EXPECT_FALSE(g.isAlive());
}
