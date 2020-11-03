#include "Game.hpp"
#include "GameState.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using JamTemplate::Game;

class GameTest : public ::testing::Test {
public:
    unsigned const windowSizeX { 100 };
    unsigned const windowSizeY { 200 };
    float const zoom { 5.0f };
    std::shared_ptr<Game> g;
    void SetUp() override { g = std::make_shared<Game>(windowSizeX, windowSizeY, zoom, "test"); }
};

TEST_F(GameTest, InitialValues)
{
    EXPECT_NE(g->getRenderTarget(), nullptr);
    EXPECT_NE(g->getRenderWindow(), nullptr);
    EXPECT_NE(g->getView(), nullptr);

    EXPECT_EQ(g->getZoom(), zoom);

    EXPECT_NEAR(g->getRenderTarget()->getSize().x, windowSizeX / zoom, 0.001);
    EXPECT_NEAR(g->getRenderTarget()->getSize().y, windowSizeY / zoom, 0.001);

    // windows returns the full size of the window, while game ctor takes only the drawable area
    EXPECT_GE(g->getRenderWindow()->getSize().x, windowSizeX);
    EXPECT_GE(g->getRenderWindow()->getSize().y, windowSizeY);

    EXPECT_EQ(g->getCamOffset().x, 0);
    EXPECT_EQ(g->getCamOffset().y, 0);
}

TEST_F(GameTest, UpdateLogic)
{
    g->update(0.5f);
    EXPECT_EQ(g->getAge(), 0.5f);

    EXPECT_TRUE(g->isAlive());
    g->kill();
    EXPECT_FALSE(g->isAlive());
}

TEST_F(GameTest, MoveCam)
{
    EXPECT_EQ(g->getCamOffset().x, 0);
    EXPECT_EQ(g->getCamOffset().y, 0);

    auto const value = 3.0f;
    g->moveCam(sf::Vector2f { value, value });
    EXPECT_NEAR(g->getCamOffset().x, value, 0.001);
    EXPECT_NEAR(g->getCamOffset().y, value, 0.001);
}

class MockState : public JamTemplate::GameState {
public:
    MOCK_METHOD(void, doInternalDraw, (), (const));
    MOCK_METHOD(void, doInternalUpdate, (float));
    MOCK_METHOD(void, doInternalCreate, ());
};

TEST_F(GameTest, CallsToActiveState)
{
    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, doInternalCreate());
    g->switchState(ms);

    float expected_update_time = 0.05f;
    EXPECT_CALL(*ms, doInternalUpdate(expected_update_time));
    g->update(expected_update_time);

    EXPECT_CALL(*ms, doInternalDraw());
    g->draw();
}
