#include "Game.hpp"
#include "GameState.hpp"
#include "RenderWindow.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using jt::Game;

#if !defined(ENABLE_WEB)

class MockWindow : public ::jt::RenderWindowInterface {
public:
    MOCK_METHOD(bool, isOpen, (), (const, override));
    MOCK_METHOD(void, checkForClose, (), (override));
    MOCK_METHOD(jt::Vector2, getSize, (), (const, override));
    MOCK_METHOD(void, draw, (std::shared_ptr<jt::Sprite>), (override));
    MOCK_METHOD(void, display, (), (override));
    MOCK_METHOD(jt::Vector2, getMousePosition, (), (override));
    MOCK_METHOD(jt::Vector2, getMousePositionScreen, (float), (override));
    MOCK_METHOD(std::shared_ptr<jt::renderTarget>, createRenderTarget, (), (override));
};

class GameTest : public ::testing::Test {
public:
    unsigned const windowSizeX { 100 };
    unsigned const windowSizeY { 200 };
    float const zoom { 1.0f };
    std::shared_ptr<Game> g { nullptr };
    std::shared_ptr<MockWindow> window { nullptr };

    void SetUp() override
    {
        window = std::make_shared<::testing::NiceMock<MockWindow>>();
        // getSize has to be called, so that the game knows how big the rendertarget will be.
        EXPECT_CALL(*window, getSize())
            .Times(::testing::AnyNumber())
            .WillRepeatedly(::testing::Return(jt::Vector2 { 100.0f, 200.0f }));
        g = std::make_shared<Game>(window, zoom);
    }
};

TEST_F(GameTest, InitialValues) { EXPECT_EQ(g->getRenderTarget(), nullptr); }

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
    // EXPECT_CALL(*ms, doInternalUpdate(expected_update_time));
    g->update(expected_update_time);

    // EXPECT_CALL(*ms, doInternalDraw());
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

TEST_F(GameTest, SetRenderTargetInvalid)
{
    EXPECT_THROW(g->setRenderTarget(nullptr), std::invalid_argument);
}

TEST_F(GameTest, GetCurrentStateNullptr) { EXPECT_EQ(g->getCurrentSate(), nullptr); }

TEST_F(GameTest, GetCurrentStateNonNullptr)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    EXPECT_NE(g->getCurrentSate(), nullptr);
}

TEST_F(GameTest, GetCurrentStateAfterSwitch)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    EXPECT_NO_THROW(g->run());
    EXPECT_NE(g->getCurrentSate(), nullptr);
}

TEST_F(GameTest, RunWithOutState) { EXPECT_NO_THROW(g->run()); }

TEST_F(GameTest, RunWithState)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    EXPECT_NO_THROW(g->run());
    EXPECT_NO_THROW(g->run());
}

TEST_F(GameTest, RunWithTwoStates)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    EXPECT_NO_THROW(g->run());
    EXPECT_NO_THROW(g->run());
    g->switchState(std::make_shared<NiceMock<MockState>>());
    EXPECT_NO_THROW(g->run());
    EXPECT_NO_THROW(g->run());
}

// TODO Add a test that verifies that cam.reset is called on swithState();

#endif
