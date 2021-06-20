#include "game.hpp"
#include "game_state.hpp"
#include "mock_window.hpp"
#include "rect_lib.hpp"
#include "render_window.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using jt::Game;

#if !defined(ENABLE_WEB)

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

TEST_F(GameTest, GameUpdateWithoutState) { g->update(0.01f); }

TEST_F(GameTest, GameUpdateCallsStateUpdateForActiveState)
{
    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, doInternalCreate());
    g->switchState(ms);

    float expected_update_time = 0.05f;
    EXPECT_CALL(*ms, doInternalUpdate(expected_update_time));
    g->update(expected_update_time);
}

TEST_F(GameTest, UpdateWithView)
{
    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, doInternalCreate());
    g->switchState(ms);

    auto view = std::make_shared<sf::View>(jt::Rect(0, 0, 100.0f, 50.0f));
    view->setViewport(jt::Rect(0, 0, 1, 1));
    g->setView(view);

    float expected_update_time = 0.05f;
    EXPECT_CALL(*ms, doInternalUpdate(expected_update_time));
    g->update(expected_update_time);
}

TEST_F(GameTest, SetViewWithRenderTarget)
{

    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillRepeatedly(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    EXPECT_NE(g->getRenderTarget(), nullptr);

    g->setView(g->getView());

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
}

TEST_F(GameTest, SwitchToNullptrState)
{
    EXPECT_THROW(g->switchState(nullptr), std::invalid_argument);
}

TEST_F(GameTest, SetNullptrRendertarget)
{
    EXPECT_THROW(g->setRenderTarget(nullptr), std::invalid_argument);
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

TEST_F(GameTest, GetCurrentStateNullptr) { EXPECT_EQ(g->getCurrentState(), nullptr); }

TEST_F(GameTest, GetCurrentStateNonNullptr)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    EXPECT_NE(g->getCurrentState(), nullptr);
}

TEST_F(GameTest, GetCurrentStateAfterSwitch)
{
    g->switchState(std::make_shared<NiceMock<MockState>>());
    EXPECT_NO_THROW(g->run());
    EXPECT_NE(g->getCurrentState(), nullptr);
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

TEST_F(GameTest, StartGameWithOneIteration)
{
    EXPECT_CALL(*window, isOpen)
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));
    auto s = std::make_shared<NiceMock<MockState>>();
    g->startGame(s, []() {});
}

TEST_F(GameTest, SetupRenderTarget)
{
    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillOnce(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    EXPECT_FLOAT_EQ(g->getView()->getSize().x, 20.0f);
    EXPECT_FLOAT_EQ(g->getView()->getSize().y, 40.0f);

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
}

TEST_F(GameTest, SetRenderTarget)
{

    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillOnce(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    EXPECT_NE(g->getRenderTarget(), nullptr);

    g->setRenderTarget(g->getRenderTarget());

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
}

TEST_F(GameTest, DrawWithRenderTargetAndState)
{
    EXPECT_CALL(*window, createRenderTarget())
        .WillOnce(::testing::Return(std::make_shared<jt::renderTarget>()));
    EXPECT_CALL(*window, getSize()).WillRepeatedly(::testing::Return(jt::Vector2 { 20.0f, 40.0f }));
    g->setupRenderTarget();
    EXPECT_NE(g->getRenderTarget(), nullptr);

    auto ms = std::make_shared<MockState>();
    EXPECT_CALL(*ms, doInternalCreate());
    g->switchState(ms);

    EXPECT_CALL(*ms, doInternalUpdate(0.1f));
    g->update(0.1f);
    EXPECT_CALL(*ms, doInternalDraw());
    g->draw();

    // cleanup so that future tests are not affected!
    jt::RenderWindow::s_view = std::shared_ptr<sf::View> { nullptr };
}

TEST_F(GameTest, GetMusicPlayer) { EXPECT_EQ(g->getMusicPlayer(), nullptr); }

// TODO Add a test that verifies that cam.reset is called on swithState();

#endif
