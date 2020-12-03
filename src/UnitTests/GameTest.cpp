#include "Game.hpp"
#include "GameState.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using jt::Game;

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

    EXPECT_NEAR(g->getRenderTarget()->getSize().x, windowSizeX / zoom, 0.001);
    EXPECT_NEAR(g->getRenderTarget()->getSize().y, windowSizeY / zoom, 0.001);

    EXPECT_EQ(g->getCamOffset().x(), 0);
    EXPECT_EQ(g->getCamOffset().y(), 0);
}

TEST_F(GameTest, UpdateLogic)
{
    g->update(0.5f);
    EXPECT_EQ(g->getAge(), 0.5f);

    EXPECT_TRUE(g->isAlive());
    g->kill();
    EXPECT_FALSE(g->isAlive());
}

TEST_F(GameTest, SetCamPosition)
{
    EXPECT_EQ(g->getCamOffset().x(), 0);
    EXPECT_EQ(g->getCamOffset().y(), 0);

    auto const value = 3.0f;
    jt::vector2 const v = { value, value };
    g->setCamOffset(v);
    EXPECT_NEAR(g->getCamOffset().x(), value, 0.001);
    EXPECT_NEAR(g->getCamOffset().y(), value, 0.001);

    g->setCamOffset(jt::vector2 { 0.0f, 0.0f });
    EXPECT_NEAR(g->getCamOffset().x(), 0.0f, 0.001);
    EXPECT_NEAR(g->getCamOffset().y(), 0.0f, 0.001);

    g->setCamOffset(v);
    EXPECT_NEAR(g->getCamOffset().x(), value, 0.001);
    EXPECT_NEAR(g->getCamOffset().y(), value, 0.001);
}

TEST_F(GameTest, MoveCam)
{
    EXPECT_EQ(g->getCamOffset().x(), 0);
    EXPECT_EQ(g->getCamOffset().y(), 0);

    g->moveCam(jt::vector2 { 0.0f, 0.0f });

    auto const value = 3.0f;
    jt::vector2 const v = { value, value };
    g->moveCam(v);
    EXPECT_NEAR(g->getCamOffset().x(), value, 0.001);
    EXPECT_NEAR(g->getCamOffset().y(), value, 0.001);

    g->moveCam(v);
    EXPECT_NEAR(g->getCamOffset().x(), 2.0f * value, 0.001);
    EXPECT_NEAR(g->getCamOffset().y(), 2.0f * value, 0.001);

    // move by zero does not move
    g->moveCam(jt::vector2 { 0.0f, 0.0f });
    EXPECT_NEAR(g->getCamOffset().x(), 2.0f * value, 0.001);
    EXPECT_NEAR(g->getCamOffset().y(), 2.0f * value, 0.001);
}

TEST_F(GameTest, DrawWithNoState) { EXPECT_NO_THROW(g->draw()); }

class MockState : public jt::GameState {
public:
    MOCK_METHOD(void, doInternalDraw, (), (const));
    MOCK_METHOD(void, doInternalUpdate, (float));
    MOCK_METHOD(void, doInternalCreate, ());
};

using ::testing::NiceMock;

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

TEST_F(GameTest, SwitchToNullptrStrate)
{
    EXPECT_THROW(g->switchState(nullptr), std::invalid_argument);
}

TEST_F(GameTest, SwitchStateTwice)
{
    auto ms1 = std::make_shared<NiceMock<MockState>>();
    auto ms2 = std::make_shared<NiceMock<MockState>>();
    // EXPECT_CALL(*ms1, doInternalCreate());
    g->switchState(ms1);

    float expected_update_time = 0.05f;
    // EXPECT_CALL(*ms1, doInternalUpdate(expected_update_time));
    g->update(expected_update_time);

    // EXPECT_CALL(*ms1, doInternalDraw());
    g->draw();
    // EXPECT_CALL(*ms2, doInternalCreate());
    g->switchState(ms2);

    // EXPECT_CALL(*ms2, doInternalUpdate(0.0f));
    // first update is required to switch the state
    g->update(0.0f);
    // EXPECT_CALL(*ms2, doInternalUpdate(expected_update_time));
    // second update will actually call the new state update
    g->update(expected_update_time);

    // EXPECT_CALL(*ms2, doInternalDraw());
    g->draw();
}

TEST_F(GameTest, SetRenderTarget) { EXPECT_NO_THROW(g->setRenderTarget(g->getRenderTarget())); }

TEST_F(GameTest, SetRenderTargetInvalid)
{
    EXPECT_THROW(g->setRenderTarget(nullptr), std::invalid_argument);
}

TEST_F(GameTest, Shake)
{
    // mock state to avoid early return
    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, doInternalCreate());
    g->switchState(ms);

    EXPECT_NO_THROW(g->shake(0.5f, 1.0f));
    // update and stay inside shake
    EXPECT_CALL(*ms, doInternalUpdate(0.3f));
    EXPECT_NO_THROW(g->update(0.3f));
    // update and leave shake
    EXPECT_CALL(*ms, doInternalUpdate(0.6f));
    EXPECT_NO_THROW(g->update(0.6f));
}

TEST_F(GameTest, SwitchStateWhileInShake)
{
    // mock state to avoid early return
    auto ms1 = std::make_shared<NiceMock<MockState>>();
    auto ms2 = std::make_shared<NiceMock<MockState>>();
    // EXPECT_CALL(*ms1, doInternalCreate());
    g->switchState(ms1);

    // EXPECT_NO_THROW(g->shake(0.5f, 1.0f));
    g->update(0.1f);
    // update and stay inside shake

    /*EXPECT_NO_THROW(g->switchState(ms2));
    EXPECT_CALL(*ms2, doInternalCreate());*/
    g->update(0.1f);
}
