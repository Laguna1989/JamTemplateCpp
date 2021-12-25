#include "game_test.hpp"
#include "action_commands/basic_action_commands.hpp"
#include "mocks/mock_state.hpp"
#include "mocks/mock_state_manager.hpp"
#include "render_window.hpp"
#include <camera.hpp>

using ::testing::NiceMock;

TEST_F(GameTest, InitialValues) { ASSERT_EQ(g->getRenderTarget(), nullptr); }

TEST_F(GameTest, DrawWithNoState) { ASSERT_NO_THROW(g->draw()); }

TEST_F(GameTest, GameUpdateWithoutState) { g->update(0.01f); }

TEST_F(GameTest, GameUpdateCallsStateUpdateForActiveState)
{
    float expected_update_time = 0.05f;
    EXPECT_CALL(*state, doInternalUpdate(expected_update_time));
    g->update(expected_update_time);
}

TEST_F(GameTest, SwitchStateTwice)
{
    auto ms1 = std::make_shared<NiceMock<MockState>>();
    auto ms2 = std::make_shared<NiceMock<MockState>>();

    g->getStateManager()->switchState(ms1);

    float expected_update_time = 0.05f;
    g->update(expected_update_time);

    g->draw();
    g->getStateManager()->switchState(ms2);

    // first update is required to switch the state
    g->update(0.0f);
    // second update will actually call the new state update
    g->update(expected_update_time);

    g->draw();
}

TEST_F(GameTest, RunWithOutState) { EXPECT_NO_THROW(g->runOneFrame()); }

TEST_F(GameTest, RunWithState)
{
    g->getStateManager()->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->runOneFrame());
    ASSERT_NO_THROW(g->runOneFrame());
}

TEST_F(GameTest, RunWithTwoStates)
{
    g->getStateManager()->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->runOneFrame());
    ASSERT_NO_THROW(g->runOneFrame());
    g->getStateManager()->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->runOneFrame());
    ASSERT_NO_THROW(g->runOneFrame());
}

TEST_F(GameTest, StartGameWithOneIteration)
{
    EXPECT_CALL(*window, isOpen)
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));
    g->getStateManager()->switchState(std::make_shared<MockState>());
    g->startGame([]() {});
}

TEST_F(GameTest, GetMusicPlayer)
{
    // compare by address if the correct entry is returend.
    ASSERT_EQ(&g->getMusicPlayer(), &musicPlayer);
}

TEST_F(GameTest, GameRunWithStateThrowingStdException)
{
    g->update(0.01f);
    EXPECT_CALL(*state, doInternalUpdate(::testing::_))
        .WillOnce(::testing::Invoke([](auto /*elapsed*/) {
            throw std::invalid_argument { "deliberately raise exception." };
        }));
    g->getStateManager()->switchState(state);
    ASSERT_THROW(g->runOneFrame(), std::invalid_argument);
}

TEST_F(GameTest, GameRunWithStateThrowingIntException)
{
    g->update(0.01f);

    ON_CALL(*state, doInternalUpdate(::testing::_))
        .WillByDefault(::testing::Invoke([](auto /*elapsed*/) { throw int { 5 }; }));
    g->getStateManager()->switchState(state);
    ASSERT_THROW(g->runOneFrame(), int);
}

TEST_F(GameTest, BasicActionCommands)
{
    addBasicActionCommands(*g);
    ASSERT_FALSE(g->getActionCommandManager()->getAllCommands().empty());
}

TEST_F(GameTest, ResetCallsResetOnCamera)
{
    EXPECT_CALL(*camera, reset);
    g->reset();
}

TEST_F(GameTest, ResetCallsResetOnInput)
{
    EXPECT_CALL(*input, reset);
    g->reset();
}

TEST_F(GameTest, GetRenderWindowDoesNotReturnNullptr) { ASSERT_NE(g->getRenderWindow(), nullptr); }

TEST_F(GameTest, GetCameraReturnsCorrectPointer) { ASSERT_EQ(g->getCamera(), camera); }

TEST(GameTestWithOutSetup, CreateWithNullptrWindow)
{
    auto func = []() {
        auto window = nullptr;
        auto input = std::make_shared<::testing::NiceMock<MockInput>>();
        auto camera = std::make_shared<jt::Camera>();
        jt::MusicPlayerNull musicPlayer;

        auto state = std::make_shared<MockState>();
        auto stateManager = std::make_shared<MockStateManager>();
        ON_CALL(*stateManager, getCurrentState).WillByDefault(::testing::Return(state));

        auto game = std::make_shared<jt::Game>(window, input, musicPlayer, camera, stateManager);
    };

    ASSERT_THROW(func(), std::invalid_argument);
}

TEST(GameTestWithOutSetup, CreateWithNullptrInput)
{
    auto func = []() {
        auto window = std::make_shared<MockWindow>();
        auto input = nullptr;
        auto camera = std::make_shared<jt::Camera>();
        jt::MusicPlayerNull musicPlayer;
        auto state = std::make_shared<MockState>();
        auto stateManager = std::make_shared<MockStateManager>();
        ON_CALL(*stateManager, getCurrentState).WillByDefault(::testing::Return(state));

        auto game = std::make_shared<jt::Game>(window, input, musicPlayer, camera, stateManager);
    };

    ASSERT_THROW(func(), std::invalid_argument);
}

TEST(GameTestWithOutSetup, CreateWithNullptrCamera)
{
    auto func = []() {
        auto window = std::make_shared<MockWindow>();
        auto input = std::make_shared<::testing::NiceMock<MockInput>>();
        auto camera = nullptr;
        jt::MusicPlayerNull musicPlayer;
        auto state = std::make_shared<MockState>();
        auto stateManager = std::make_shared<MockStateManager>();
        ON_CALL(*stateManager, getCurrentState).WillByDefault(::testing::Return(state));

        auto game = std::make_shared<jt::Game>(window, input, musicPlayer, camera, stateManager);
    };

    ASSERT_THROW(func(), std::invalid_argument);
}

TEST(GameTestWithOutSetup, CreateWithNullptrStateManager)
{
    auto func = []() {
        auto window = std::make_shared<MockWindow>();
        auto input = std::make_shared<::testing::NiceMock<MockInput>>();
        auto camera = std::make_shared<jt::Camera>();
        jt::MusicPlayerNull musicPlayer;
        auto stateManager = nullptr;

        auto game = std::make_shared<jt::Game>(window, input, musicPlayer, camera, stateManager);
    };

    ASSERT_THROW(func(), std::invalid_argument);
}
