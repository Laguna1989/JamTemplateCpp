#include "game_test.hpp"
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

TEST_F(GameTest, SetNullptrRendertarget)
{
    ASSERT_THROW(g->setRenderTarget(nullptr), std::invalid_argument);
}

TEST_F(GameTest, SwitchStateTwice)
{
    auto ms1 = std::make_shared<NiceMock<MockState>>();
    auto ms2 = std::make_shared<NiceMock<MockState>>();

    g->stateManager()->switchState(ms1);

    float expected_update_time = 0.05f;
    g->update(expected_update_time);

    g->draw();
    g->stateManager()->switchState(ms2);

    // first update is required to switch the state
    g->update(0.0f);
    // second update will actually call the new state update
    g->update(expected_update_time);

    g->draw();
}

TEST_F(GameTest, SetRenderTargetInvalid)
{
    ASSERT_THROW(g->setRenderTarget(nullptr), std::invalid_argument);
}

TEST_F(GameTest, RunWithOutState) { EXPECT_NO_THROW(g->run()); }

TEST_F(GameTest, RunWithState)
{
    g->stateManager()->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->run());
    ASSERT_NO_THROW(g->run());
}

TEST_F(GameTest, RunWithTwoStates)
{
    g->stateManager()->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->run());
    ASSERT_NO_THROW(g->run());
    g->stateManager()->switchState(std::make_shared<NiceMock<MockState>>());
    ASSERT_NO_THROW(g->run());
    ASSERT_NO_THROW(g->run());
}

TEST_F(GameTest, StartGameWithOneIteration)
{
    EXPECT_CALL(*window, isOpen)
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));
    g->stateManager()->switchState(std::make_shared<MockState>());
    g->startGame([]() {});
}

TEST_F(GameTest, GetMusicPlayer) { ASSERT_EQ(g->getMusicPlayer(), music_player); }

TEST_F(GameTest, GameRunWithStateThrowingStdException)
{
    g->update(0.01f);
    EXPECT_CALL(*state, doInternalUpdate(::testing::_))
        .WillOnce(::testing::Invoke([](auto /*elapsed*/) {
            throw std::invalid_argument { "deliberately raise exception." };
        }));
    g->stateManager()->switchState(state);
    ASSERT_THROW(g->run(), std::invalid_argument);
}

// TODO
/*
TEST_F(GameTest, GetCurrentStateDirectlyAfterSwitch)
{
    auto state1 = std::make_shared<MockState>();
    g->stateManager()->switchState(state1);
    ASSERT_EQ(g->getCurrentState(), state1);
}*/

TEST_F(GameTest, GameRunWithStateThrowingIntException)
{
    g->update(0.01f);

    ON_CALL(*state, doInternalUpdate(::testing::_))
        .WillByDefault(::testing::Invoke([](auto /*elapsed*/) { throw int { 5 }; }));
    g->stateManager()->switchState(state);
    ASSERT_THROW(g->run(), int);
}

TEST_F(GameTest, GetRenderWindowDoesNotReturnNullptr) { ASSERT_NE(g->getRenderWindow(), nullptr); }

TEST_F(GameTest, GetCameraReturnsCorrectPointer) { ASSERT_EQ(g->getCamera(), camera); }

TEST(GameTestWithOutSetup, CreateWithNullptrWindow)
{
    auto func = []() {
        auto window = nullptr;
        auto input = std::make_shared<::testing::NiceMock<MockInput>>();
        auto camera = std::make_shared<jt::Camera>();
        auto musicPlayer = std::make_shared<jt::MusicPlayerNull>();

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
        auto musicPlayer = std::make_shared<jt::MusicPlayerNull>();
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
        auto musicPlayer = std::make_shared<jt::MusicPlayerNull>();
        auto state = std::make_shared<MockState>();
        auto stateManager = std::make_shared<MockStateManager>();
        ON_CALL(*stateManager, getCurrentState).WillByDefault(::testing::Return(state));

        auto game = std::make_shared<jt::Game>(window, input, musicPlayer, camera, stateManager);
    };

    ASSERT_THROW(func(), std::invalid_argument);
}

TEST(GameTestWithOutSetup, CreateWithNullptrMusicPlayer)
{
    auto func = []() {
        auto window = std::make_shared<MockWindow>();
        auto input = std::make_shared<::testing::NiceMock<MockInput>>();
        auto camera = std::make_shared<jt::Camera>();
        auto musicPlayer = nullptr;
        auto state = std::make_shared<MockState>();
        auto stateManager = std::make_shared<MockStateManager>();
        ON_CALL(*stateManager, getCurrentState).WillByDefault(::testing::Return(state));

        auto game = std::make_shared<jt::Game>(window, input, musicPlayer, camera, stateManager);
    };

    ASSERT_THROW(func(), std::invalid_argument);
}
